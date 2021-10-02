#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include "shaders.h"
#include "buffers.h"

namespace tbe
{
    class TB_Cube
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

        float scaleC[24] = {
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f
        };

        float positionC[24] = {
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f
        };

        const float psrConst[24] = {
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
        //initialize cube
        void init(const std::string & fragName, const std::string & vertName, const int drawType, const float color[], size_t colorSizeof);
        //draw cube
        void draw(glm::mat4x4 pvm);
        //set position of cube
        void SetPosition(float x, float y, float z);
        //set position of cube
        void SetPosition(glm::vec3 position);
        //set scale of cube
        void SetScale(float scale);
        //set scale of cube
        void SetScale(float x, float y, float z);
        //set scale of cube
        void SetScale(glm::vec3 scale);
        //set color of cube
        void SetColor(float color[], size_t colorSizeof);
        //delete cube
        void deleteCube();
    };

    typedef TB_Cube Cube;
}