#include "imgui.h"
#include "menus/Gauges.hpp"
#include "raylib.h"
#include "rlImGui.h"

#include "draw.hpp"
#include "lights.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "menus/BottomBar.hpp"
#include "menus/BurgerMenu.hpp"
#include "menus/StatusBar.hpp"
#include "menus/Debug.hpp"

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
    Debug debug;
    BurgerMenu burgerMenu;
    BottomBar bottomBar;
    StatusBar statusBar;
    Gauges gauges;

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
        if (IsKeyPressed(KEY_I)) {
            draw.toggleFloorState();
        }
        if (IsKeyPressed(KEY_O)) {
            draw.toggleSpeedoState();
        }
        draw.Car();
        draw.Floor();

        // End Draw Calls
        EndShaderMode();
        EndMode3D();

        rlImGuiBegin();
        gauges.Render();
        ImVec2 speedoPos = gauges.getSpeedoPos();
        ImVec2 speedoSize = gauges.getSpeedoSize();
        draw.Speedometer(speedoPos, speedoSize, debug.getSpeed()); // Must draw 2D objects such as a Rectangle outside of 3D Mode

        bottomBar.Render();
        statusBar.Render();
        burgerMenu.Render();
        debug.Render();
        rlImGuiEnd();
        EndDrawing();
    }
    rlImGuiShutdown();
    CloseWindow();
    return 1;
}
