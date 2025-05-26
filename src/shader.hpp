#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "raylib.h"

auto inline CreateShader() -> Shader {
    Shader shader = LoadShader("../assets/shaders/testshader.vs", "../assets/shaders/testshader.fs");
    return shader;
}

#endif
