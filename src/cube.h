#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include "shaders.h"
#include "buffers.h"

class Cube
{
private:
    //unsigned int vao, vbo[2], ebo;
    Vao vao;
    Vbo vbo[2];
    Ebo ebo;
    Shader sh;

    float vertices[24] = {
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f
    };

    const float scaleConst[24] = {
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f
    };

    unsigned int indices[36] = {
        0, 1, 2,
        1, 2, 3,
        4, 5, 6,
        5, 6, 7,
        0, 2, 4,
        2, 4, 6,
        1, 3, 5,
        3, 5, 7,
        0, 1, 4,
        1, 4, 5,
        2, 3, 6,
        3, 6, 7
    };

public:
    void init(const std::string & fragName, const std::string & vertName, const int drawType, const float color[], const unsigned long colorSizeof);
    void draw(glm::mat4x4 pvm);
    void SetPosition(float x, float y, float z);
    void SetPosition(glm::vec3 position);
    void SetScale(float scale);
    void SetScale(float x, float y, float z);
    void SetScale(glm::vec3 scale);
    void SetColor(float color[], unsigned int colorSizeof);
    void deleteCube();
};