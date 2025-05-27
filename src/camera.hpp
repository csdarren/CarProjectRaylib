#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <algorithm>

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

    float distance; // Distance from origin
    float pitch;    // Vertical rotation
    float yaw;      // Horizontal rotation

  public:
    CustomCamera() : distance(BEGIN_DISTANCE), pitch(PITCH_DEGRADE * DEG2RAD), yaw(CAM_FOV * DEG2RAD) {
        this->camera.up = CAM_UP;
        this->camera.position = CAM_POS;
        this->camera.target = CAM_TARGET;
        this->camera.fovy = CAM_FOV;
        this->camera.projection = CAMERA_PERSPECTIVE;
    };
    void CustomCameraUpdate() { // MATH CAMERA SHIT I DONT UNDERSTAND THANKS GPT

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 delta = GetMouseDelta();
            static constexpr float SENSITIVITY = 0.003F;
            static constexpr float MIN_PITCH_OFFSET = 0.1F;
            static constexpr float MAX_PITCH_OFFSET = 0.2F;
            static constexpr float MAX_DISTANCE = 15.0F;
            static constexpr float MIN_DISTANCE = 5.0F;

            // Yaw = Horizontal rotation movement
            yaw -= delta.x * SENSITIVITY;
            // Pitch = Vertical rotation movement
            pitch += delta.y * SENSITIVITY;
            // Distance = Distance to target
            distance -= GetMouseWheelMove();

            // Clamp pitch to avoid flipping the camera

            pitch = Clamp(pitch, (-PI / 2) + MIN_PITCH_OFFSET, (PI / 2) - MAX_PITCH_OFFSET);
            pitch = std::max(pitch, MAX_PITCH_OFFSET);
            distance = std::max(distance, MIN_DISTANCE);
            distance = std::min(distance, MAX_DISTANCE);
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
