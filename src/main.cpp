#include <array>
#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"

#include "shader.hpp"
#include "camera.hpp"
#include "gui.hpp"

// RLIGHTS_IMPLEMENTATION MUST BE DEFINED BEFORE LOADING rlights.h
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#define GLSL_VERSION 330

namespace {

void rayInit(int fps, Vector2 screenSize) {
    SetTargetFPS(fps);
    InitWindow(static_cast<int>(screenSize.x), static_cast<int>(screenSize.y), "CarProjectRaylib");
}
void DrawModel(Model model, Vector3 modelPosition) {
    for (int i = 0; i < model.materialCount; i++) {
        DrawModel(model, modelPosition, 1.0F, WHITE);
    }
}

}   // namespace

auto main() -> int {
    static const int FPS = 60;
    const Vector2 screenSize{1280, 720};
    rayInit(FPS, screenSize);

    Model carModel = LoadModel("../assets/models/MiniCooper.glb");
    Vector3 modelPosition = {0.0F, 0.0F, 0.0F};
    Shader shader = CreateShader();
    const Vector3 LightPosition = {0, 4, 5};
    std::array<Light, MAX_LIGHTS> lights = {CreateLight(LIGHT_POINT, LightPosition, Vector3Zero(), YELLOW, shader)};
    CustomCamera cam;

    rlImGuiSetup(true);
    BottomBar bottomBar;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_Y)) {
            lights[0].enabled = !lights[0].enabled;   // Makes lights equal the opposite state (on off switch)
        }
        for (Light &light : lights) {
            UpdateLightValues(shader, light);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        rlImGuiBegin();
        BeginMode3D(cam.GetCustomCamera());
        BeginShaderMode(shader);

        cam.CustomCameraUpdate();

        // Draw Calls
        const Vector2 PlaneDimensions{1000.0, 1000.0};
        DrawPlane(Vector3Zero(), PlaneDimensions, GRAY);
        DrawModel(carModel, modelPosition);

        // End Draw Calls
        EndShaderMode();
        EndMode3D();

        bottomBar.Render();
        rlImGuiEnd();
        EndDrawing();
    }
    rlImGuiShutdown();
    UnloadShader(shader);
    UnloadModel(carModel);
    CloseWindow();
    return 1;
}
