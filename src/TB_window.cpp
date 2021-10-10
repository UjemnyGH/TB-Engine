#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "TB_window.h"

tbe::TB_Window::TB_Window(int argc, char** argv, const char* windowName)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutInitWindowSize(800, 600);

    glutCreateWindow("Window");

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        std::cout << "!GLEW_OK\n";
    }

    if(!GLEW_VERSION_4_3)
    {
        std::cout << "!GLEW_VERSION_4_3\n";
    }

    glGetError();

    glEnable(GL_DEPTH_TEST);
}

void tbe::TB_Window::basicErrorChecking()
{
    switch (glGetError())
    {
    case GL_INVALID_ENUM:
        std::cout << "Invalid enum\n";
        break;

    case GL_INVALID_FRAMEBUFFER_OPERATION:
        std::cout << "Invalid framebuffer operation\n";
        break;

    case GL_INVALID_INDEX:
        std::cout << "Invalid index\n";
        break;

    case GL_INVALID_OPERATION:
        std::cout << "Invalid operation\n";
        break;
    
    case GL_INVALID_VALUE:
        std::cout << "Invalid value\n";
        break;

    case GL_STACK_OVERFLOW:
        std::cout << "Stack overflow\n";
        break;

    case GL_STACK_UNDERFLOW:
        std::cout << "Stack underflow\n";
        break;

    case GL_CONTEXT_LOST:
        std::cout << "Context lost\n";
        break;

    case GL_OUT_OF_MEMORY:
        std::cout << "Out of memory\n";
        break;

    case GL_NO_ERROR:
        break;
    }
}