#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "buffers.h"
#include "shaders.h"

namespace tbe
{
    class TB_Mesh
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
        //init mesh
        void init(const std::string & fragName, const std::string & vertName, const std::string & meshName, const int drawType, const float color[], const unsigned long colorSizeof);
        //draw mesh
        void draw(glm::mat4x4 pvm);
        //set position of mesh
        void SetPosition(float x, float y, float z);
        //set position of mesh
        void SetPosition(glm::vec3 pos);
        //set scale of mesh
        void SetScale(float scale);
        //set scale of mesh
        void SetScale(float x, float y, float z);
        //set scale of mesh
        void SetScale(glm::vec3 scale);
        //set color of mesh
        void SetColor(float color[], size_t colorSize);
        //delete mesh
        void deleteMesh();
    };

    typedef TB_Mesh Mesh;
}