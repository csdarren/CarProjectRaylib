#pragma once
#ifndef SHADER_H
#define SHADER_H

Shader CreateShader()
{
    Shader shader = LoadShader("C:/dev/CPP/CarProjectRaylib/assets/shaders/testshader.vs",
                               "C:/dev/CPP/CarProjectRaylib/assets/shaders/testshader.fs");
    return shader;
}

#endif