#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "cube.h"
#include "shaders.h"
#include "buffers.h"

void tbe::TB_Cube::init(const std::string & fragName, const std::string & vertName, const int drawType, const float color[], size_t colorSizeof)
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

void tbe::TB_Cube::SetPosition(float x, float y, float z)
{
    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        positionC[i * 3] = psrConst[i * 3];
        positionC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        positionC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = scaleC[i * 3] + ((x * positionC[i * 3]) * psrConst[i * 3]);
        vertices[(i * 3) + 1] = scaleC[(i * 3) + 1] + ((y * positionC[(i * 3) + 1]) * psrConst[(i * 3) + 1]);
        vertices[(i * 3) + 2] = scaleC[(i * 3) + 2] + ((z * positionC[(i * 3) + 2]) * psrConst[(i * 3) + 2]);
    }

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPosition(glm::vec3 position)
{
    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        positionC[i * 3] = psrConst[i * 3];
        positionC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        positionC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = scaleC[i * 3] + ((position.x * positionC[i * 3]) * psrConst[i * 3]);
        vertices[(i * 3) + 1] = scaleC[(i * 3) + 1] + ((position.y * positionC[(i * 3) + 1]) * psrConst[(i * 3) + 1]);
        vertices[(i * 3) + 2] = scaleC[(i * 3) + 2] + ((position.z * positionC[(i * 3) + 2]) * psrConst[(i * 3) + 2]);
    }

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetScale(float scale)
{
    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 4; i++)
    {
        scaleC[i] = psrConst[i];

        vertices[i] = scale * scaleC[i];
    }

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetScale(float x, float y, float z)
{
    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        scaleC[i * 3] = psrConst[i * 3];
        scaleC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        scaleC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = x * scaleC[i * 3];
        vertices[(i * 3) + 1] = y * scaleC[(i * 3) + 1];
        vertices[(i * 3) + 2] = z * scaleC[(i * 3) + 2];
    }

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetScale(glm::vec3 scale)
{
    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        scaleC[i * 3] = psrConst[i * 3];
        scaleC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        scaleC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = scale.x * scaleC[i * 3];
        vertices[(i * 3) + 1] = scale.y * scaleC[(i * 3) + 1];
        vertices[(i * 3) + 2] = scale.z * scaleC[(i * 3) + 2];
    }

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(float x, float y, float z, float scale)
{
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(float x, float y, float z, float sX, float sY, float sZ)
{
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(float x, float y, float z, glm::vec3 scale)
{
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(glm::vec3 pos, float scale)
{
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(glm::vec3 pos, float sX, float sY, float sZ)
{
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(glm::vec3 pos, glm::vec3 scale)
{
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetColor(float color[], size_t colorSizeof)
{
    vao.bindVao();
    vbo[1].bindVbo(color, colorSizeof, 3, 1, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::draw(glm::mat4x4 pvm, int drawType)
{
    vao.bindVao();
    glUseProgram(sh.ID);

    glUniformMatrix4fv(glGetUniformLocation(sh.ID, "pvm"), 1, GL_FALSE, glm::value_ptr(pvm));

    glDrawElements(drawType, sizeof(vertices) / 2, GL_UNSIGNED_INT, NULL);

    vao.unbindVao();
    glUseProgram(0);
}

void tbe::TB_Cube::SetCollisionTrue(bool collisionTrue)
{
    collisionsOn = collisionTrue;
}

void tbe::TB_Cube::deleteCube()
{
    vao.deleteVao();
    vbo->deleteVbo();
    ebo.deleteEbo();
    glDeleteProgram(sh.ID);
}