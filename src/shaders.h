#pragma once
#include <string>

unsigned int LoadShader(const int & type, const std::string & name);

class Shader
{
public:
    unsigned int ID;
    Shader(){}
    Shader(const std::string & vertName, const std::string & fragName);
};