#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "buffers.h"
#include "shaders.h"

class Mesh
{
private:
    Vao vao;
    Vbo vbo[2];
    Ebo ebo;
    Shader sh;

    std::vector<float> vertices;
    std::vector<float> textureVertices;
    std::vector<float> uvNormals;

    std::vector<float> psrConst;
    std::vector<float> positionC;
    std::vector<float> scaleC;

    std::vector<unsigned int> indices;
    std::vector<unsigned int> textureIndices;
    std::vector<unsigned int> normalsIndices;

public:
    void init(const std::string & fragName, const std::string & vertName, const std::string & meshName, const int drawType, const float color[], const unsigned long colorSizeof);
    void draw(glm::mat4x4 pvm);
    void SetPosition(float x, float y, float z);
    void SetPosition(glm::vec3 pos);
    void SetScale(float scale);
    void SetScale(float x, float y, float z);
    void SetScale(glm::vec3 scale);
    void SetColor(float color[], size_t colorSize);
    void deleteMesh();
};