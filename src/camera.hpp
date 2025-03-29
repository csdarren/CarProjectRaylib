#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>

class CustomCamera {
  private:
    Camera3D camera;
    float distance; // Distance from the target
    float yaw;      // Horizontal rotation
    float pitch;    // Vertical rotation
    float sensitivity;

  public:
    CustomCamera()
        : distance(15.0f), yaw(45.0f * DEG2RAD), pitch(20.0f * DEG2RAD), sensitivity(0.003f) {
        camera = {0};
        camera.position = Vector3{10.0f, 5.0f, 10.0f};
        camera.target = Vector3{0.0f, 0.0f, 0.0f};
        camera.up = Vector3{0.0f, 1.0f, 0.0f};
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;
    };
    ~CustomCamera() {};
    void CustomCameraUpdate() { // MATH CAMERA SHIT I DONT UNDERSTAND THANKS GPT
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 delta = GetMouseDelta();

            // Yaw = Horizontal rotation movement
            yaw -= delta.x * sensitivity;
            // Pitch = Vertical rotation movement
            pitch += delta.y * sensitivity;
            // Distance = Distance to target
            distance -= GetMouseWheelMove();

            // Clamp pitch to avoid flipping the camera
            pitch = Clamp(pitch, -PI / 2 + 0.1f, PI / 2 - 0.1f);
            if (pitch < 0.2f) {
                pitch = 0.2f;
            }
            if (distance < 5.0f) {
                distance = 5.0f;
            }
            if (distance > 15.0f) {
                distance = 15.0f;
            }
        }
        // Convert spherical to Cartesian (set camera position)
        camera.position.x = camera.target.x + distance * cosf(pitch) * sinf(yaw);
        camera.position.y = camera.target.y + distance * sinf(pitch);
        camera.position.z = camera.target.z + distance * cosf(pitch) * cosf(yaw);
    };
    Camera GetCustomCamera() {
        return camera;
    }
};
#endif