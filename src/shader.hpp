#pragma once
#ifndef SHADER_H
#define SHADER_H

Shader CreateShader() {
    Shader shader = LoadShader("../assets/shaders/testshader.vs", "../assets/shaders/testshader.fs");
    return shader;
}

#endif