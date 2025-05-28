#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "raylib.h"

class CustomShader {
  private:
    Shader shader{};

  public:
    CustomShader() {
        this->shader = LoadShader("../assets/shaders/testshader.vs", "../assets/shaders/testshader.fs");
    }

    CustomShader(const CustomShader &) = default;
    CustomShader(CustomShader &&) = delete;
    auto operator=(const CustomShader &) -> CustomShader & = default;
    auto operator=(CustomShader &&) -> CustomShader & = delete;

    ~CustomShader() {
        UnloadShader(shader);
    }
    auto getShader() -> Shader {
        return shader;
    }
};

#endif
