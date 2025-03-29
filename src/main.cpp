#include "Master.h"

void DrawOpaqueMeshes(Model model, Shader shader, Vector3 modelPosition) {
    for (int i = 0; i < model.materialCount; i++) {
        Material mat = model.materials[model.meshMaterial[i]];
        if (mat.maps[MATERIAL_MAP_DIFFUSE].color.a == 255) {
            mat.shader = shader;
            DrawMesh(model.meshes[i], mat, MatrixIdentity());
            //DrawModelEx(model, modelPosition, Vector3{0, 1, 0}, 0.0f, Vector3{1, 1, 1}, WHITE);
            //DrawModel(model, modelPosition, 1.0f, WHITE);
            std::cout << "Material Count: " << model.materialCount << std::endl;
            std::cout << "Material: " << model.meshMaterial << std::endl;
        }
    }
}

void DrawTransparentMeshes(Model model, Shader shader, Vector3 modelPosition) {
    rlDisableDepthMask();
    rlDisableBackfaceCulling(); // Ensure both sides of glass are visible

    for (int i = 0; i < model.meshCount; i++) {
        Material mat = model.materials[model.meshMaterial[i]];
        mat.shader = shader;
        DrawMesh(model.meshes[i], mat, MatrixIdentity());
    }

    rlEnableDepthMask();
    rlEnableBackfaceCulling();
}

int main() {
    const Vector2 screenSize{1280, 720};

    InitWindow(screenSize.x, screenSize.y, "CarProjectRaylib");
    SetTargetFPS(60);

    Model carModel = LoadModel("C:/dev/CPP/CarProjectRaylib/assets/models/MiniCooper.glb");
    Vector3 modelPosition = {0.0f, 0.0f, 0.0f};
    Shader shader = CreateShader();

    Light lights[MAX_LIGHTS] = {lights[0] = CreateLight(LIGHT_POINT, Vector3{0, 4, 5}, Vector3Zero(), Color{50, 50, 50, 255}, shader)};

    CustomCamera c;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_Y)) {
            lights[0].enabled = !lights[0].enabled; // Makes lights equal the opposite state (on off switch)
        }
        for (int i = 0; i < MAX_LIGHTS; i++) {
            UpdateLightValues(shader, lights[i]);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(c.GetCustomCamera());
        BeginShaderMode(shader);

        c.CustomCameraUpdate();

        // Draw Calls
        DrawPlane(Vector3Zero(), Vector2{1000.0, 1000.0}, Color{100, 100, 100, 255});
        DrawOpaqueMeshes(carModel, shader, modelPosition);
        DrawTransparentMeshes(carModel, shader, modelPosition);

        // End Draw Calls
        EndShaderMode();
        EndMode3D();
        EndDrawing();
    }
    UnloadShader(shader);
    UnloadModel(carModel);
    CloseWindow();
}