#pragma once

namespace tbe
{
    static const char* colorVS = "data/shaders/colorShaders/colorVS.glsl";
    static const char* colorFS = "data/shaders/colorShaders/colorFS.glsl";

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