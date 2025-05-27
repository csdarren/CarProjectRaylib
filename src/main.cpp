// TODO: Abstract shader loading and handling into its own class (BE CAREFUL, CAUSED SEGFAULT ERROR LAST TIME)
// Abstract lights into its own class, Also be careful, could cause SEGFAULT
// Abstract Draw commands into its own class, consider editing the way models are loaded into an array of models
// Add HUD to the top of the screen with the time, other basic info
#include "draw.hpp"
#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"

#include "lights.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "gui.hpp"

#define GLSL_VERSION 330

namespace {

void rayInit() {
    static const int FPS = 60;
    const Vector2 screenSize{1280, 720};
    SetTargetFPS(FPS);
    InitWindow(static_cast<int>(screenSize.x), static_cast<int>(screenSize.y), "CarProjectRaylib");
    rlImGuiSetup(true);
}

} // namespace

auto main() -> int {
    rayInit();

    CustomShader shader;
    CustomLights lightSource(shader.getShader());
    CustomCamera cam;
    Draw draw;
    ImVec2 ScreenSize;
    Gui gui;
    BurgerMenu burgerMenu;
    BottomBar bottomBar;
    StatusBar statusBar;

    while (!WindowShouldClose()) {
        lightSource.UpdateLights();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(cam.GetCustomCamera());
        BeginShaderMode(shader.getShader());

        cam.CustomCameraUpdate();

        // Draw Calls
        const Vector2 PlaneDimensions{1000.0, 1000.0};
        DrawPlane(Vector3Zero(), PlaneDimensions, GRAY);
        draw.Car();

        // End Draw Calls
        EndShaderMode();
        EndMode3D();

        rlImGuiBegin();
        bottomBar.Render();
        statusBar.Render();
        burgerMenu.Render();
        rlImGuiEnd();
        EndDrawing();
    }
    rlImGuiShutdown();
    UnloadShader(shader.getShader());
    CloseWindow();
    return 1;
}
