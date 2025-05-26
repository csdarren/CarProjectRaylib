#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "raylib.h"
#include "raymath.h"

class CustomCamera {
  private:
    Camera3D camera{0};

    static constexpr float CAM_FOV = 45.0F;
    static constexpr Vector3 CAM_UP = {0.0F, 1.0F, 0.0F};
    static constexpr Vector3 CAM_TARGET = {0.0F, 0.0F, 0.0F};
    static constexpr Vector3 CAM_POS = {10.0F, 5.0F, 10.0F};

    static constexpr float BEGIN_DISTANCE = 15.0F;
    static constexpr float PITCH_DEGRADE = 20.0F;
    static constexpr float SENSITIVITY = 0.003F;

    float distance;   // Distance from origin
    float pitch;      // Vertical rotation
    float yaw;        // Horizontal rotation

  public:
    CustomCamera() : distance(BEGIN_DISTANCE), pitch(PITCH_DEGRADE * DEG2RAD), yaw(CAM_FOV * DEG2RAD) {
        this->camera.up = CAM_UP;
        this->camera.position = CAM_POS;
        this->camera.target = CAM_TARGET;
        this->camera.fovy = CAM_FOV;
        this->camera.projection = CAMERA_PERSPECTIVE;
    };
    void CustomCameraUpdate() {   // MATH CAMERA SHIT I DONT UNDERSTAND THANKS GPT

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 delta = GetMouseDelta();
            // Yaw = Horizontal rotation movement
            yaw -= delta.x * SENSITIVITY;
            // Pitch = Vertical rotation movement
            pitch += delta.y * SENSITIVITY;
            // Distance = Distance to target
            distance -= GetMouseWheelMove();

            // Clamp pitch to avoid flipping the camera
            pitch = Clamp(pitch, (-PI / 2) + 0.1F, PI / 2 - 0.1F);
            if (pitch < 0.2F) {
                pitch = 0.2F;
            }
            if (distance < 5.0F) {
                distance = 5.0F;
            }
            if (distance > 15.0F) {
                distance = 15.0F;
            }
        }
        // Convert spherical to Cartesian (set camera position)
        camera.position.x = camera.target.x + distance * cosf(pitch) * sinf(yaw);
        camera.position.y = camera.target.y + distance * sinf(pitch);
        camera.position.z = camera.target.z + distance * cosf(pitch) * cosf(yaw);
    };
    auto GetCustomCamera() -> Camera {
        return camera;
    }
};
#endif
