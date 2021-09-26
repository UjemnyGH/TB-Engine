#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "cube.h"
#include "shaders.h"
#include "buffers.h"

void Cube::init(const std::string & fragName, const std::string & vertName, const int drawType, const float color[], const unsigned long colorSizeof)
{
    sh = Shader(vertName, fragName);

    vao.create();
    vao.bindVao();

    vbo[0].create();
    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, drawType);

    vbo[1].create();
    vbo[1].bindVbo(color, colorSizeof, 3, 1, drawType);

    ebo.create();
    ebo.bindEbo(indices, sizeof(indices), drawType);

    vao.unbindVao();
}

void Cube::SetPosition(float x, float y, float z)
{
    
}

void Cube::SetPosition(glm::vec3 position)
{

}

void Cube::SetScale(float scale)
{
    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 4; i++)
    {
        vertices[i] = scale * scaleConst[i];
    }

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void Cube::SetScale(float x, float y, float z)
{
    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        vertices[i * 3] = x * scaleConst[i * 3];
        vertices[(i * 3) + 1] = y * scaleConst[(i * 3) + 1];
        vertices[(i * 3) + 2] = z * scaleConst[(i * 3) + 2];
    }

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void Cube::SetScale(glm::vec3 scale)
{
    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        vertices[i * 3] = scale.x * scaleConst[i * 3];
        vertices[(i * 3) + 1] = scale.y * scaleConst[(i * 3) + 1];
        vertices[(i * 3) + 2] = scale.z * scaleConst[(i * 3) + 2];
    }

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void Cube::SetColor(float color[], unsigned int colorSizeof)
{
    vao.bindVao();
    vbo[1].bindVbo(color, colorSizeof, 3, 1, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void Cube::draw(glm::mat4x4 pvm)
{
    vao.bindVao();
    glUseProgram(sh.ID);

    glUniformMatrix4fv(glGetUniformLocation(sh.ID, "pvm"), 1, GL_FALSE, glm::value_ptr(pvm));

    glDrawElements(GL_TRIANGLES, sizeof(vertices) / 8, GL_UNSIGNED_INT, NULL);

    vao.bindVao();
    glUseProgram(0);
}



void Cube::deleteCube()
{
    vao.deleteVao();
    vbo->deleteVbo();
    ebo.deleteEbo();
    glDeleteProgram(sh.ID);
}