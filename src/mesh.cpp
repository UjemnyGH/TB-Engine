#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "mesh.h"

/*class Mesh
{
private:
    Vao vao;
    Vbo vbo[2];
    Ebo ebo;
    Shader sh;

public:
    void init(const std::string & fragName, const std::string & vertName, const int drawType, const float color[], const unsigned long colorSizeof);
    void draw(glm::mat4x4 pvm);
    void SetPosition(float x, float y, float z);
    void SetPosition(glm::vec3 pos);
    void SetScale(float scale);
    void SetScale(float x, float y, float z);
    void SetScale(glm::vec3 scale);
    void deleteMesh();
};*/

void Mesh::init(const std::string & fragName, const std::string & vertName, const std::string & meshName, const int drawType, const float color[], const unsigned long colorSizeof)
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

            std::cout << "X: " << indX << ", "  << texX << ", "  << norX << ",Y: "  << indY << ", "  << texY << ", "  << norY << ",Z: "  << indZ << ", "  << texZ << ", "  << norZ << std::endl;

            std::cout << "Slash num: " << slashNum << " " << lastSlashIX << std::endl;
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

    for(int i = 0; i < vertices.size() / 3; i++)
    {
        std::cout << "V: " << vertices[i * 3] << ", " << vertices[i * 3 + 1] << ", " << vertices[i * 3 + 2] << std::endl;
    }

    for(int i = 0; i < indices.size() / 3; i++)
    {
        std::cout << "In: " << indices[i * 3] << ", " << indices[i * 3 + 1] << ", " << indices[i * 3 + 2] << std::endl;
    }
}

void Mesh::draw(glm::mat4x4 pvm)
{
    vao.bindVao();
    glUseProgram(sh.ID);

    glUniformMatrix4fv(glGetUniformLocation(sh.ID, "pvm"), 1, GL_FALSE, glm::value_ptr(pvm));

    glDrawElements(GL_TRIANGLES, vertices.size() * 2, GL_UNSIGNED_INT, NULL);

    vao.unbindVao();
    glUseProgram(0);
}

void Mesh::deleteMesh()
{
    vao.deleteVao();
    vbo->deleteVbo();
    ebo.deleteEbo();
    glDeleteProgram(sh.ID);
}