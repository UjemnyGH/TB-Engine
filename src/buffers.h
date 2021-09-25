#pragma once

class Vao
{
private:
    unsigned int ID;
public:
    Vao();
    void create();
    void bindVao();
    void unbindVao();
    void deleteVao();
};

class Vbo
{
private:
    unsigned int ID;
public:
    Vbo();
    void create();
    void bindVbo(const float table[], const unsigned long tableSize, const unsigned short dimensions, const unsigned int index, const int drawType);
    void deleteVbo();
};

class Ebo
{
private:
    unsigned int ID;
public:
    Ebo();
    void create();
    void bindEbo(const unsigned int table[], const unsigned long tableSize, const int drawType);
    void deleteEbo();
};