#include "Master.h"

void RayInit(int fps, const Vector2 screenSize);
void DrawOpaqueMeshes(Model model, Shader shader, Vector3 modelPosition);
void DrawTransparentMeshes(Model model, Shader shader, Vector3 modelPosition);

int main() {
    const Vector2 screenSize{1280, 720};
    RayInit(60, screenSize);

    Model carModel = LoadModel("../assets/models/MiniCooper.glb");
    Vector3 modelPosition = {0.0f, 0.0f, 0.0f};
    Shader shader = CreateShader();
    const int MAX_UI_TEXTURES = 10;
    Texture Burger = LoadTexture("../assets/images/Hamburger.png");
    Texture UITextures[MAX_UI_TEXTURES] = {Burger};
    Light lights[MAX_LIGHTS] = {lights[0] = CreateLight(LIGHT_POINT, Vector3{0, 4, 5}, Vector3Zero(), Color{50, 50, 50, 255}, shader)};
    CustomCamera c;

    rlImGuiSetup(true);
    Gui gui;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_Y)) {
            lights[0].enabled = !lights[0].enabled; // Makes lights equal the opposite state (on off switch)
        }
        for (int i = 0; i < MAX_LIGHTS; i++) {
            UpdateLightValues(shader, lights[i]);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        rlImGuiBegin();
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

        ImGui::SetNextWindowPos(gui.GetBottomBarPos(), true);
        ImGui::SetNextWindowSize(gui.GetBottomBarSize(), true);
        gui.BottomBarWindow(Burger);
        rlImGuiEnd();
        EndDrawing();
    }
    rlImGuiShutdown();
    UnloadShader(shader);
    UnloadModel(carModel);
    CloseWindow();
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

void DrawOpaqueMeshes(Model model, Shader shader, Vector3 modelPosition) {
    for (int i = 0; i < model.materialCount; i++) {
        Material mat = model.materials[model.meshMaterial[i]];
        mat.shader = shader;
        DrawModel(model, modelPosition, 1.0f, WHITE);
    }
}

void RayInit(int fps, const Vector2 screenSize) {
    SetTargetFPS(fps);
    InitWindow(screenSize.x, screenSize.y, "CarProjectRaylib");
}