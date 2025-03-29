#include "Master.h"

const int SHADOW_MAP_SIZE = 1024;
RenderTexture2D shadowMap;
Matrix lightViewMatrix, lightProjection;

void DrawOpaqueMeshes(Model model, Shader shader, Vector3 modelPosition) 
{
    for (int i = 0; i < model.materialCount; i++) 
    {
        Material mat = model.materials[model.meshMaterial[i]];
        if (mat.maps[MATERIAL_MAP_DIFFUSE].color.a == 255) 
        {
            mat.shader = shader;
            DrawMesh(model.meshes[i], mat, MatrixIdentity());
            DrawModelEx(model, modelPosition, Vector3{0, 1, 0}, 0.0f, Vector3{1, 1, 1}, WHITE);
        }
    }
}

void DrawTransparentMeshes(Model model, Shader shader, Vector3 modelPosition) {
    rlDisableDepthMask();
    rlDisableBackfaceCulling(); // Ensure both sides of glass are visible

    for (int i = 0; i < model.meshCount; i++) 
    {
        Material mat = model.materials[model.meshMaterial[i]];
        if (mat.maps[MATERIAL_MAP_DIFFUSE].color.a < 255 || 
            mat.maps[MATERIAL_MAP_DIFFUSE].texture.format == PIXELFORMAT_UNCOMPRESSED_R8G8B8A8) 
            {
                mat.shader = shader;
                DrawMesh(model.meshes[i], mat, MatrixIdentity());
                //DrawModelEx(model, modelPosition, Vector3{0, 1, 0}, 0.0f, Vector3{1, 1, 1}, WHITE);
        }
    }

    rlEnableDepthMask();
    rlEnableBackfaceCulling();
}

int main()
{
    const Vector2 screenSize{1280, 720};

    InitWindow(screenSize.x, screenSize.y, "CarProjectRaylib");
    SetTargetFPS(60);

    shadowMap = LoadRenderTexture(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
    SetTextureFilter(shadowMap.texture, TEXTURE_FILTER_BILINEAR);


    Camera camera = {0};    
    camera.position = Vector3{6.0f, 6.0f, 6.0f}; // Camera position
    camera.target = Vector3{0.0f, 2.0f, 0.0f};   // Camera looking at point
    camera.up = Vector3{0.0f, 1.0f, 0.0f};       // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                         // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;      // Camera projection type

    Camera3D lightCamera;
    lightCamera.position = (Vector3){ 4.0f, 6.0f, 10.0f }; // Light position
    lightCamera.target = (Vector3){ 0.0f, 2.0f, 0.0f };    // Where the light looks
    lightCamera.up = (Vector3){ 0.0f, 1.0f, 0.0f };        // Up direction
    lightCamera.fovy = 90.0f;                              // Field of view
    lightCamera.projection = CAMERA_ORTHOGRAPHIC;         // Orthographic or perspective

    Matrix lightView = MatrixLookAt(lightCamera.position, lightCamera.target, lightCamera.up);
    Matrix lightProjection = MatrixOrtho(-10, 10, -10, 10, 1.0f, 50.0f); // Orthographic
    Matrix lightSpaceMatrix = MatrixMultiply(lightProjection, lightView);

    Model carModel = LoadModel("C:/dev/CPP/CarProjectRaylib/assets/models/MiniCooper.glb");
    Vector3 modelPosition = {0.0f, 0.0f, 0.0f};

    //struct Anim
    //{
    //    int animsCount = 0;
    //    unsigned int animIndex = 0;
    //    unsigned int animCurrentFrame = 0;
    //    ModelAnimation *modelAnimations = LoadModelAnimations("C:/dev/CPP/CarProjectRaylib/assets/models/MiniCooper.glb", &animsCount);
    //};

    Shader shader = CreateShader();
    Light lights[MAX_LIGHTS] = {0};
    lights[0] = CreateLight(LIGHT_POINT, Vector3{0, 4, 5}, Vector3Zero(), Color{ 50, 50, 50, 255 }, shader);

    BeginTextureMode(shadowMap);
        ClearBackground(BLACK); // Depth map background
        BeginMode3D(lightCamera); // Render from light's perspective
    
        for (int i = 0; i < carModel.meshCount; i++) {
            DrawMesh(carModel.meshes[i], carModel.materials[i], MatrixIdentity());
        }
        
            EndMode3D();
        EndTextureMode();

    while (!WindowShouldClose())
    {
        HideCursor();
        

        UpdateCamera(&camera, CAMERA_FREE);
        DisableCursor();
        float cameraPos[3] = {camera.position.x, camera.position.y, camera.position.z};
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            camera.position = {0, 0, 0};
        }
        //if (IsKeyDown(KEY_LEFT))
        //{
        //    lights[0].position.x -= 0.1;
        //}
        //if (IsKeyDown(KEY_RIGHT))
        //{
        //    lights[0].position.x += 0.1;
        //}
        //if (IsKeyDown(KEY_UP))
        //{
        //    lights[0].position.y += 0.1;
        //}
        //if (IsKeyDown(KEY_DOWN))
        //{
        //    lights[0].position.y -= 0.1;
        //}

        if (IsKeyDown(KEY_LEFT))
        {
            modelPosition.x += 0.1;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            modelPosition.x -= 0.1;
        }
        if (IsKeyDown(KEY_UP))
        {
            modelPosition.z += 0.1;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            modelPosition.z -= 0.1;
        }

        if (IsKeyPressed(KEY_Y))
        {
            lights[0].enabled = !lights[0].enabled;
        }
        for (int i = 0; i < MAX_LIGHTS; i++) 
            UpdateLightValues(shader, lights[i]);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        BeginShaderMode(shader);

        DrawPlane(Vector3Zero(), Vector2{1000.0, 1000.0}, Color{100,100,100,255});

        EndShaderMode();

        
        for (int i = 0; i < MAX_LIGHTS; i++)
        {
            if (lights[i].enabled)
                DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
            else
                DrawSphereWires(lights[i].position, 0.2f, 8, 8, ColorAlpha(lights[i].color, 0.3f));
        }

        BoundingBox carBoundingBox = GetModelBoundingBox(carModel);
        DrawBoundingBox(carBoundingBox, RED);

        //DrawGrid(1000, 1.0f);

        DrawOpaqueMeshes(carModel, shader,modelPosition);
        
        DrawTransparentMeshes(carModel, shader, modelPosition);

        EndMode3D();

        EndDrawing();
    }
    UnloadShader(shader);
    UnloadModel(carModel);
    CloseWindow();
}