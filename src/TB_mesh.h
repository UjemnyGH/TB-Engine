#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "TB_buffers.h"
#include "TB_shaders.h"

namespace tbe
{
    class TB_Mesh
    {
    private:
        Vao vao;
        Vbo vbo[2];
        Ebo ebo;
        Shader sh;

        float cpX, cpY, cpZ, csX, csY, csZ, crX, crY, crZ;

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
        void draw(glm::mat4x4 pvm, int drawType);
        //get position of cube
        glm::vec3 GetPosition();
        //get scale of cube
        glm::vec3 GetScale();
        //get rotation of cube
        glm::vec3 GetRotation();
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
        //set scale and position of mesh
        void SetPositionScale(float x, float y, float z, float scale);
        //set scale and position of mesh
        void SetPositionScale(float x, float y, float z, float sX, float sY, float sZ);
        //set scale and position of mesh
        void SetPositionScale(float x, float y, float z, glm::vec3 scale);
        //set scale and position of mesh
        void SetPositionScale(glm::vec3 pos, float scale);
        //set scale and position of mesh
        void SetPositionScale(glm::vec3 pos, float sX, float sY, float sZ);
        //set scale and position of mesh
        void SetPositionScale(glm::vec3 pos, glm::vec3 scale);
        //set color of mesh
        void SetColor(float color[], size_t colorSize);
        //delete mesh
        void deleteMesh();
    };

    typedef TB_Mesh Mesh;
}