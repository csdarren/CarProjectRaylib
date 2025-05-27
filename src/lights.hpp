#pragma once
#ifndef LIGHTS_HPP
#define LIGHTS_HPP
#include <array>
// RLIGHTS_IMPLEMENTATION MUST BE DEFINED BEFORE LOADING rlights.h
#define RLIGHTS_IMPLEMENTATION
#include "raylib.h"
#include "raymath.h"
#include "rlights.h"

class CustomLights {
  private:
    Shader shader{};
    Vector3 lightPosition{};
    std::array<Light, MAX_LIGHTS> lights{};
    static constexpr Vector3 LIGHT_POS = {0, 4, 5};

  public:
    CustomLights(Shader shader)
        : shader(shader) {
        this->lights = {CreateLight(LIGHT_POINT, LIGHT_POS, Vector3Zero(), YELLOW, this->shader)};
    }
    auto UpdateLights() -> void {
        if (IsKeyPressed(KEY_Y)) {
            lights[0].enabled = !lights[0].enabled; // Makes lights equal the opposite state (on off switch)
        }
        for (Light &light : lights) {
            UpdateLightValues(this->shader, light);
        }
    }
};

#endif
