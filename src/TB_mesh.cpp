#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "TB_mesh.h"

void tbe::TB_Mesh::init(const std::string & fragName, const std::string & vertName, const std::string & meshName, const int drawType, const float color[], const unsigned long colorSizeof)
{
    std::ifstream f;
    
    f.open(meshName, std::ios::binary);

    if(!f)
    {
        std::cout << "No file";
    }

    std::string line;

    while(!f.eof())
    {
        std::getline(f, line);

        if(line.find("v ") == 0)
        {
            std::stringstream ss(line.c_str() + 2);
            float x, y, z;
            ss >> x >> y >> z;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            if(x > 0)
            {
                psrConst.push_back(1);
            }
            else
            {
                psrConst.push_back(-1);
            }

            if(y > 0)
            {
                psrConst.push_back(1);
            }
            else
            {
                psrConst.push_back(-1);
            }

            if(z > 0)
            {
                psrConst.push_back(1);
            }
            else
            {
                psrConst.push_back(-1);
            }

            scaleC.push_back(x);
            scaleC.push_back(y);
            scaleC.push_back(z);

            positionC.push_back(x);
            positionC.push_back(y);
            positionC.push_back(z);
        }
        else if(line.find("vt ") == 0)
        {
            std::stringstream ss(line.c_str() + 3);
            float u, v, w;
            ss >> u >> v >> w;

            textureVertices.push_back(u);
            textureVertices.push_back(v);
            textureVertices.push_back(w);
        }
        else if(line.find("vn ") == 0)
        {
            std::stringstream ss(line.c_str() + 3);
            float x, y, z;
            ss >> x >> y >> z;

            uvNormals.push_back(x);
            uvNormals.push_back(y);
            uvNormals.push_back(z);
        }
        else if(line.find("f ") == 0)
        {
            int slashNum = 0;
            size_t lastSlashIX = 0;
            bool doubleSlash = false;

            for(size_t i = 0; i < line.size(); i++)
            {
                if(line[i] == '/')
                {
                    line[i] = ' ';

                    lastSlashIX = i;
                    slashNum++;
                }
            }

            std::stringstream ss(line.c_str() + 2);

            unsigned int indX = 0, texX = 0, norX = 0, indY = 0, texY = 0, norY = 0, indZ = 0, texZ = 0, norZ = 0, indW = 0, texW = 0, norW = 0;

            ss >> indX >> texX >> norX >> indY >> texY >> norY >> indZ >> texZ >> norZ >> indW >> texW >> norW;

            indices.push_back(indX - 1);
            indices.push_back(indY - 1);
            indices.push_back(indZ - 1);

            indices.push_back(indX - 1);
            indices.push_back(indZ - 1);
            indices.push_back(indW - 1);

            textureIndices.push_back(texX - 1);
            textureIndices.push_back(texY - 1);
            textureIndices.push_back(texZ - 1);

            textureIndices.push_back(texX - 1);
            textureIndices.push_back(texZ - 1);
            textureIndices.push_back(texW - 1);

            normalsIndices.push_back(norX - 1);
            normalsIndices.push_back(norY - 1);
            normalsIndices.push_back(norZ - 1);
 
            normalsIndices.push_back(norX - 1);
            normalsIndices.push_back(norZ - 1);
            normalsIndices.push_back(norW - 1);
        }
    }

    sh = Shader(vertName, fragName);

    vao.create();
    vao.bindVao();

    vbo[0].create();
    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, drawType);

    vbo[1].create();
    vbo[1].bindVbo(color, colorSizeof, 3, 1, drawType);

    ebo.create();
    ebo.bindEbo(indices.data(), sizeof(int) * indices.size(), drawType);

    vao.unbindVao();
}

void tbe::TB_Mesh::draw(glm::mat4x4 pvm, int drawType)
{
    vao.bindVao();
    glUseProgram(sh.ID);

    glUniformMatrix4fv(glGetUniformLocation(sh.ID, "pvm"), 1, GL_FALSE, glm::value_ptr(pvm));

    glDrawElements(drawType, vertices.size() * 2, GL_UNSIGNED_INT, NULL);

    vao.unbindVao();
    glUseProgram(0);
}

glm::vec3 tbe::TB_Mesh::GetPosition()
{
    return glm::vec3(cpX, cpY, cpZ);
}

glm::vec3 tbe::TB_Mesh::GetScale()
{
    return glm::vec3(csX, csY, csZ);
}

glm::vec3 tbe::TB_Mesh::GetRotation()
{
    return glm::vec3(crX, crY, crZ);
}

void tbe::TB_Mesh::SetPosition(float x, float y, float z)
{
    cpX = x;
    cpY = y;
    cpZ = z;

    vao.bindVao();

    for(int i = 0; i < (sizeof(float) * vertices.size()) / 12; i++)
    {
        positionC[i * 3] = psrConst[i * 3];
        positionC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        positionC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = scaleC[i * 3] + ((x * positionC[i * 3]) * psrConst[i * 3]);
        vertices[(i * 3) + 1] = scaleC[(i * 3) + 1] + ((y * positionC[(i * 3) + 1]) * psrConst[(i * 3) + 1]);
        vertices[(i * 3) + 2] = scaleC[(i * 3) + 2] + ((z * positionC[(i * 3) + 2]) * psrConst[(i * 3) + 2]);
    }

    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Mesh::SetPosition(glm::vec3 pos)
{
    cpX = pos.x;
    cpY = pos.y;
    cpZ = pos.z;

    vao.bindVao();

    for(int i = 0; i < (sizeof(float) * vertices.size()) / 12; i++)
    {
        positionC[i * 3] = psrConst[i * 3];
        positionC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        positionC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = scaleC[i * 3] + ((pos.x * positionC[i * 3]) * psrConst[i * 3]);
        vertices[(i * 3) + 1] = scaleC[(i * 3) + 1] + ((pos.y * positionC[(i * 3) + 1]) * psrConst[(i * 3) + 1]);
        vertices[(i * 3) + 2] = scaleC[(i * 3) + 2] + ((pos.z * positionC[(i * 3) + 2]) * psrConst[(i * 3) + 2]);
    }

    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Mesh::SetScale(float scale)
{
    csX = scale;
    csY = scale;
    csZ = scale;

    vao.bindVao();

    for(int i = 0; i < (sizeof(float) * vertices.size()) / 4; i++)
    {
        scaleC[i] = psrConst[i];

        vertices[i] = scale * scaleC[i];
    }

    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Mesh::SetScale(float x, float y, float z)
{
    csX = x;
    csY = y;
    csZ = z;

    vao.bindVao();

    for(int i = 0; i < (sizeof(float) * vertices.size()) / 12; i++)
    {
        scaleC[i * 3] = psrConst[i * 3];
        scaleC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        scaleC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = x * scaleC[i * 3];
        vertices[(i * 3) + 1] = y * scaleC[(i * 3) + 1];
        vertices[(i * 3) + 2] = z * scaleC[(i * 3) + 2];
    }

    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Mesh::SetScale(glm::vec3 scale)
{
    csX = scale.x;
    csY = scale.y;
    csZ = scale.z;

    vao.bindVao();

    for(int i = 0; i < (sizeof(float) * vertices.size()) / 12; i++)
    {
        scaleC[i * 3] = psrConst[i * 3];
        scaleC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        scaleC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = scale.x * scaleC[i * 3];
        vertices[(i * 3) + 1] = scale.y * scaleC[(i * 3) + 1];
        vertices[(i * 3) + 2] = scale.z * scaleC[(i * 3) + 2];
    }

    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Mesh::SetPositionScale(float x, float y, float z, float scale)
{
    cpX = x;
    cpY = y;
    cpZ = z;

    csX = scale;
    csY = scale;
    csZ = scale;

    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        positionC[i * 3] = psrConst[i * 3];
        positionC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        positionC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        scaleC[i * 3] = psrConst[i * 3];
        scaleC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        scaleC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = scale * scaleC[i * 3] + ((x * positionC[i * 3]) * psrConst[i * 3]);
        vertices[(i * 3) + 1] = scale * scaleC[(i * 3) + 1] + ((y * positionC[(i * 3) + 1]) * psrConst[(i * 3) + 1]);
        vertices[(i * 3) + 2] = scale * scaleC[(i * 3) + 2] + ((z * positionC[(i * 3) + 2]) * psrConst[(i * 3) + 2]);
    }

    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Mesh::SetPositionScale(float x, float y, float z, float sX, float sY, float sZ)
{
    cpX = x;
    cpY = y;
    cpZ = z;

    csX = sX;
    csY = sY;
    csZ = sZ;

    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        positionC[i * 3] = psrConst[i * 3];
        positionC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        positionC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        scaleC[i * 3] = psrConst[i * 3];
        scaleC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        scaleC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = sX * scaleC[i * 3] + ((x * positionC[i * 3]) * psrConst[i * 3]);
        vertices[(i * 3) + 1] = sY * scaleC[(i * 3) + 1] + ((y * positionC[(i * 3) + 1]) * psrConst[(i * 3) + 1]);
        vertices[(i * 3) + 2] = sZ * scaleC[(i * 3) + 2] + ((z * positionC[(i * 3) + 2]) * psrConst[(i * 3) + 2]);
    }

    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Mesh::SetPositionScale(float x, float y, float z, glm::vec3 scale)
{
    cpX = x;
    cpY = y;
    cpZ = z;

    csX = scale.x;
    csY = scale.y;
    csZ = scale.z;

    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        positionC[i * 3] = psrConst[i * 3];
        positionC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        positionC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        scaleC[i * 3] = psrConst[i * 3];
        scaleC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        scaleC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = scale.x * scaleC[i * 3] + ((x * positionC[i * 3]) * psrConst[i * 3]);
        vertices[(i * 3) + 1] = scale.y * scaleC[(i * 3) + 1] + ((y * positionC[(i * 3) + 1]) * psrConst[(i * 3) + 1]);
        vertices[(i * 3) + 2] = scale.z * scaleC[(i * 3) + 2] + ((z * positionC[(i * 3) + 2]) * psrConst[(i * 3) + 2]);
    }

    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Mesh::SetPositionScale(glm::vec3 pos, float scale)
{
    cpX = pos.x;
    cpY = pos.y;
    cpZ = pos.z;

    csX = scale;
    csY = scale;
    csZ = scale;

    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        positionC[i * 3] = psrConst[i * 3];
        positionC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        positionC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        scaleC[i * 3] = psrConst[i * 3];
        scaleC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        scaleC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = scale * scaleC[i * 3] + ((pos.x * positionC[i * 3]) * psrConst[i * 3]);
        vertices[(i * 3) + 1] = scale * scaleC[(i * 3) + 1] + ((pos.y * positionC[(i * 3) + 1]) * psrConst[(i * 3) + 1]);
        vertices[(i * 3) + 2] = scale * scaleC[(i * 3) + 2] + ((pos.z * positionC[(i * 3) + 2]) * psrConst[(i * 3) + 2]);
    }

    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Mesh::SetPositionScale(glm::vec3 pos, float sX, float sY, float sZ)
{
    cpX = pos.x;
    cpY = pos.y;
    cpZ = pos.z;

    csX = sX;
    csY = sY;
    csZ = sZ;

    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        positionC[i * 3] = psrConst[i * 3];
        positionC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        positionC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        scaleC[i * 3] = psrConst[i * 3];
        scaleC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        scaleC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = sX * scaleC[i * 3] + ((pos.x * positionC[i * 3]) * psrConst[i * 3]);
        vertices[(i * 3) + 1] = sY * scaleC[(i * 3) + 1] + ((pos.y * positionC[(i * 3) + 1]) * psrConst[(i * 3) + 1]);
        vertices[(i * 3) + 2] = sZ * scaleC[(i * 3) + 2] + ((pos.z * positionC[(i * 3) + 2]) * psrConst[(i * 3) + 2]);
    }

    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Mesh::SetPositionScale(glm::vec3 pos, glm::vec3 scale)
{
    cpX = pos.x;
    cpY = pos.y;
    cpZ = pos.z;

    csX = scale.x;
    csY = scale.y;
    csZ = scale.z;

    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        positionC[i * 3] = psrConst[i * 3];
        positionC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        positionC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        scaleC[i * 3] = psrConst[i * 3];
        scaleC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        scaleC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = scale.x * scaleC[i * 3] + ((pos.x * positionC[i * 3]) * psrConst[i * 3]);
        vertices[(i * 3) + 1] = scale.y * scaleC[(i * 3) + 1] + ((pos.y * positionC[(i * 3) + 1]) * psrConst[(i * 3) + 1]);
        vertices[(i * 3) + 2] = scale.z * scaleC[(i * 3) + 2] + ((pos.z * positionC[(i * 3) + 2]) * psrConst[(i * 3) + 2]);
    }

    vbo[0].bindVbo(vertices.data(), sizeof(float) * vertices.size(), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Mesh::SetColor(float color[], size_t colorSize)
{
    vao.bindVao();

    vbo[1].bindVbo(color, colorSize, 3, 1, GL_DYNAMIC_DRAW);

    vao.unbindVao();
}


void tbe::TB_Mesh::deleteMesh()
{
    vao.deleteVao();
    vbo->deleteVbo();
    ebo.deleteEbo();
    glDeleteProgram(sh.ID);
}