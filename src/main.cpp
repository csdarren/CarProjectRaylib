#include "raylib.h"
#include "rlImGui.h"

#include "draw.hpp"
#include "lights.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "menus/BottomBar.hpp"
#include "menus/BurgerMenu.hpp"
#include "menus/StatusBar.hpp"

#define GLSL_VERSION 330

namespace {

void rayInit() {
    static const int FPS = 60;
    const Vector2 screenSize{1280, 720};
    SetTargetFPS(FPS);
    InitWindow(static_cast<int>(screenSize.x), static_cast<int>(screenSize.y), "CarProjectRaylib");
    rlImGuiSetup(true);
}

auto StartDrawing() -> void {
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

} // namespace

auto main() -> int {
    rayInit();

    CustomShader shader;
    CustomLights lightSource(shader.getShader());
    CustomCamera cam;

    Draw draw;

    Gui gui;
    BurgerMenu burgerMenu;
    BottomBar bottomBar;
    StatusBar statusBar;

    while (!WindowShouldClose()) {
        lightSource.UpdateLights();

        StartDrawing();
        BeginMode3D(cam.GetCustomCamera());
        BeginShaderMode(shader.getShader());

        cam.CustomCameraUpdate();

        // Draw Calls

        if (IsKeyPressed(KEY_U)) {
            draw.toggleCarState();
        }
        Draw::Floor();
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
    CloseWindow();
    return 1;
}
