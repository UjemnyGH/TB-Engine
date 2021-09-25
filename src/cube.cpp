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