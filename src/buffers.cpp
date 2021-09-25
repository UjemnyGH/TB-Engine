#define GLEWW_STATIC
#include <GL/glew.h>
#include <iostream>
#include "buffers.h"

Vao::Vao()
{
    
}

void Vao::create()
{
    glGenVertexArrays(1, &ID);
}

void Vao::bindVao()
{
    glBindVertexArray(ID);
}

void Vao::unbindVao()
{
    glBindVertexArray(0);
}

void Vao::deleteVao()
{
    glDeleteVertexArrays(1, &ID);
}

Vbo::Vbo()
{
    
}

void Vbo::create()
{
    glGenBuffers(1, &ID);
}

void Vbo::bindVbo(const float table[], const unsigned long tableSize, const unsigned short dimensions, const unsigned int index, const int drawType)
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, tableSize, table, drawType);
    glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(index);
}

void Vbo::deleteVbo()
{
    glDeleteBuffers(1, &ID);
}

Ebo::Ebo()
{

}

void Ebo::create()
{
    glGenBuffers(1, &ID);
}

void Ebo::bindEbo(const unsigned int table[], const unsigned long tableSize, const int drawType)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tableSize, table, drawType);
}

void Ebo::deleteEbo()
{
    glDeleteBuffers(1, &ID);
}