#pragma once

namespace tbe
{
    class TB_Vao
    {
    private:
        unsigned int ID;

    public:
        TB_Vao();
        //creating vertex array object
        void create();
        //bind vertex array object
        void bindVao();
        //unbind vertex array object (glBindVertexArray(0))
        void unbindVao();
        //delete vertex array object
        void deleteVao();
    };

    class TB_Vbo
    {
    private:
        unsigned int ID;

    public:
        TB_Vbo();
        //create vertex buffer object
        void create();
        //bind vertex buffer object
        void bindVbo(const float table[], const unsigned long tableSize, const unsigned short dimensions, const unsigned int index, const int drawType);
        //delete vertex buffer object
        void deleteVbo();
    };

    class TB_Ebo
    {
    private:
        unsigned int ID;

    public:
        TB_Ebo();
        //create element buffer object
        void create();
        //bind element buffer object
        void bindEbo(const unsigned int table[], const unsigned long tableSize, const int drawType);
        //delete element buffer object
        void deleteEbo();
    };

    class TB_Texture
    {
    private:
        unsigned int ID;
        int width, height, normalChannels;
        unsigned char* data;

    public:
        TB_Texture();
        //create texture
        void create();
        //bind texture
        void bindTexture(const std::string path, const int wrapping);
        //bind texture
        void bindTexture();
        //unbind texture
        void unbindTexture();
        //delete texture
        void deleteTexture();
    };

    typedef TB_Vao Vao;
    typedef TB_Vbo Vbo;
    typedef TB_Ebo Ebo;
    typedef TB_Texture Texture;
}