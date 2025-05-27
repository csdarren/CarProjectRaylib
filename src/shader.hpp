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
    auto getShader() -> Shader {
        return shader;
    }
};

#endif
