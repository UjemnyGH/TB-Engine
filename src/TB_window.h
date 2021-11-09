#pragma once

namespace tbe
{
    static const char* colorVS = "data/shaders/colorShaders/colorVS.glsl";
    static const char* colorFS = "data/shaders/colorShaders/colorFS.glsl";

    static const char* textureVS = "data/shaders/textureShaders/textureVS.glsl";
    static const char* textureFS = "data/shaders/textureShaders/textureFS.glsl";

    class TB_Window
    {
    private:

    public:
        TB_Window()
        {

        }
        //Init and create window
        TB_Window(int argc, char** argv, const char* windowName);

        void basicErrorChecking();
    };

    typedef TB_Window Window;
}