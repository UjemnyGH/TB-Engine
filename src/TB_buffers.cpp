#define GLEWW_STATIC
#include <GL/glew.h>
#include <iostream>
#include "TB_buffers.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

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

tbe::TB_Texture::TB_Texture()
{

}

void tbe::TB_Texture::create()
{
    glGenTextures(1, &ID);
}

void tbe::TB_Texture::bindTexture(const std::string path, const int wrapping)
{
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(1);

    data = stbi_load(path.c_str(), &width, &height, &normalChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_INT, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Error liading image: " << path << std::endl;
    }

    stbi_image_free(data);
}

void tbe::TB_Texture::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void tbe::TB_Texture::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void tbe::TB_Texture::deleteTexture()
{
    glDeleteTextures(1, &ID);
}