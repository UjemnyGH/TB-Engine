#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include "shaders.h"

unsigned int LoadShader(const int & type, const std::string & name)
{
    std::ifstream f;
    
    f.open(name, std::ios::binary);

    if(f.bad())
    {
        return 37;
    }

    f.seekg(0, std::ios::end);

    int len = static_cast<int>(f.tellg());

    f.seekg(0, std::ios::beg);

    char* srcBuffer = new char[(len + 1) * sizeof(char)];
    f.read(srcBuffer, len);
    srcBuffer[len] = '\0';
    f.close();

    unsigned shader = glCreateShader(type);

    glShaderSource(shader, 1, const_cast<char**>(&srcBuffer), NULL);

    delete[] srcBuffer;

    glCompileShader(shader);

    return shader;
}

Shader::Shader(const std::string & vertName, const std::string & fragName)
{
    ID = glCreateProgram();
    glAttachShader(ID, LoadShader(GL_VERTEX_SHADER, vertName));
    glAttachShader(ID, LoadShader(GL_FRAGMENT_SHADER, fragName));
    glLinkProgram(ID);
}