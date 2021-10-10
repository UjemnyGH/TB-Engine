#define GLEWW_STATIC
#include <GL/glew.h>
#include <iostream>
#include "TB_buffers.h"

tbe::TB_Vao::TB_Vao()
{
    
}

void tbe::TB_Vao::create()
{
    glGenVertexArrays(1, &ID);
}

void tbe::TB_Vao::bindVao()
{
    glBindVertexArray(ID);
}

void tbe::TB_Vao::unbindVao()
{
    glBindVertexArray(0);
}

void tbe::TB_Vao::deleteVao()
{
    glDeleteVertexArrays(1, &ID);
}

tbe::TB_Vbo::TB_Vbo()
{
    
}

void tbe::TB_Vbo::create()
{
    glGenBuffers(1, &ID);
}

void tbe::TB_Vbo::bindVbo(const float table[], const unsigned long tableSize, const unsigned short dimensions, const unsigned int index, const int drawType)
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, tableSize, table, drawType);
    glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(index);
}

void tbe::TB_Vbo::deleteVbo()
{
    glDeleteBuffers(1, &ID);
}

tbe::TB_Ebo::TB_Ebo()
{

}

void tbe::TB_Ebo::create()
{
    glGenBuffers(1, &ID);
}

void tbe::TB_Ebo::bindEbo(const unsigned int table[], const unsigned long tableSize, const int drawType)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tableSize, table, drawType);
}

void tbe::TB_Ebo::deleteEbo()
{
    glDeleteBuffers(1, &ID);
}