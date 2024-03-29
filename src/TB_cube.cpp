#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "TB_cube.h"
#include "TB_shaders.h"
#include "TB_buffers.h"
#include "TB_engine_variables.h"

void tbe::TB_Cube::init(const std::string & fragName, const std::string & vertName, const int drawType, const float color[], size_t colorSizeof)
{
    texturesEnabled = false;
    
    sh = Shader(vertName, fragName);

    vao.create();
    vao.bindVao();

    vbo[0].create();
    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, drawType);

    vbo[1].create();
    vbo[1].bindVbo(color, colorSizeof, 3, 1, drawType);

    vbo[2].create();

    ebo.create();
    ebo.bindEbo(indices, sizeof(indices), drawType);

    vao.unbindVao();
}

void tbe::TB_Cube::init(const std::string & fragName, const std::string & vertName, const std::string textureName, const int drawType, const float color[], size_t colorSizeof)
{
    texturesEnabled = true;

    sh = Shader(vertName, fragName);

    vao.create();
    vao.bindVao();

    vbo[0].create();
    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, drawType);

    vbo[1].create();
    vbo[1].bindVbo(color, colorSizeof, 3, 1, drawType);

    vbo[2].create();
    vbo[2].bindVbo(texturePoints, sizeof(texturePoints), 2, 2, drawType);

    texture.create();
    texture.bindTexture(textureName, GL_REPEAT);

    ebo.create();
    ebo.bindEbo(indices, sizeof(indices), drawType);

    glUseProgram(sh.ID);

    glUniform1i(glGetUniformLocation(sh.ID, "tex"), 0);

    glUseProgram(0);

    vao.unbindVao();
}

glm::vec3 tbe::TB_Cube::GetPosition()
{
    return glm::vec3(cpX, cpY, cpZ);
}

glm::vec3 tbe::TB_Cube::GetScale()
{
    return glm::vec3(csX, csY, csZ);
}

glm::vec3 tbe::TB_Cube::GetRotation()
{
    return glm::vec3(crX, crY, crZ);
}

void tbe::TB_Cube::SetPosition(float x, float y, float z)
{
    cpX = x;
    cpY = y;
    cpZ = z;

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
    cpX = position.x;
    cpY = position.y;
    cpZ = position.z;

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
    csX = scale;
    csY = scale;
    csZ = scale;

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
    csX = x;
    csY = y;
    csZ = z;

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
    csX = scale.x;
    csY = scale.y;
    csZ = scale.z;

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

//TODO: Rotations
//FIXME: Rotations
//NOTDONE: Rotations
//Fix it
//Try to fix that shit
//F-I-X--T-H-I-S
//That down there !!!FIXIT!!!
//Do it
//FIX IT THAT NOT THAT HARD
//TRYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY TO FIX THAT PIECE OF SHIT
/**
 * @brief YOU MUST SEE THIS
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * SEE SO REPAIR
 */
/**
 * @brief WHAT THE FUCK I DONT REPAIR THIS !!!!!!!!!!!!!!!!!!!REPAIR!!!!!!!!!!!!!!!!!!!!!!!!
 * 
 */
/**
 * @brief SCREW THAT PIECE OF SHIT - DELETE IT BECOUS YOU NEVER FIX IT
 */
void tbe::Cube::SetRotation(float x, float y, float z)
{
    vao.bindVao();

    for(int i = 0; i < sizeof(vertices) / 12; i++)
    {
        rotationC[i * 3] = psrConst[i * 3];
        rotationC[(i * 3) + 1] = psrConst[(i * 3) + 1];
        rotationC[(i * 3) + 2] = psrConst[(i * 3) + 2];

        vertices[i * 3] = (cos(glm::radians(x)) * cos(glm::radians(y))) * rotationC[i + 3];
        vertices[(i * 3) + 1] = (sin(glm::radians(y))) * rotationC[(i + 3) + 1];
    }

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(float x, float y, float z, float scale)
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(float x, float y, float z, float sX, float sY, float sZ)
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(float x, float y, float z, glm::vec3 scale)
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(glm::vec3 pos, float scale)
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(glm::vec3 pos, float sX, float sY, float sZ)
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetPositionScale(glm::vec3 pos, glm::vec3 scale)
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

    vbo[0].bindVbo(vertices, sizeof(vertices), 3, 0, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::SetColor(float color[], size_t colorSizeof)
{
    vao.bindVao();
    vbo[1].bindVbo(color, colorSizeof, 3, 1, GL_DYNAMIC_DRAW);
    vao.unbindVao();
}

void tbe::TB_Cube::draw(glm::mat4x4 pvm, int drawMode)
{
    vao.bindVao();
    glUseProgram(sh.ID);
    if(texturesEnabled)
    {
        texture.bindTexture();
    }

    glUniformMatrix4fv(glGetUniformLocation(sh.ID, "pvm"), 1, GL_FALSE, glm::value_ptr(pvm));

    glDrawElements(drawMode, sizeof(vertices) / 2, GL_UNSIGNED_INT, NULL);

    vao.unbindVao();
    glUseProgram(0);
}

void tbe::TB_Cube::SetCollisionTrue(bool collisionTrue)
{
    collisionsOn = collisionTrue;
}

void tbe::TB_Cube::SetTexture(const std::string path, const int wrapping)
{
    glUseProgram(sh.ID);
    vao.bindVao();

    texture.bindTexture(path, wrapping);

    glUseProgram(0);
    vao.unbindVao();
}

void tbe::TB_Cube::deleteCube()
{
    vao.deleteVao();
    vbo->deleteVbo();
    ebo.deleteEbo();
    glDeleteProgram(sh.ID);
    texture.deleteTexture();
}