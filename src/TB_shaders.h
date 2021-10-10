#pragma once
#include <string>

namespace tbe
{
    //return compiles shader from file
    unsigned int LoadShader(const int & type, const std::string & name);

    class TB_Shader
    {
    public:
        //shader (program ID)
        unsigned int ID;
        TB_Shader(){}
        //shader initialize with vertex / fragment shader
        TB_Shader(const std::string & vertName, const std::string & fragName);
    };

    typedef TB_Shader Shader;
}