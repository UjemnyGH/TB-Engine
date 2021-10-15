#include <GL/freeglut.h>
#include <iostream>
#include "TB_time.h"

float tbe::TB_Time::deltaTime()
{
    currentFrame = (float)glutGet(GLUT_ELAPSED_TIME);
    deltaFrame = currentFrame - lastFrame;
    lastFrame = currentFrame;

    return deltaFrame;
}

double tbe::TB_Time::time()
{
    return glutGet(GLUT_ELAPSED_TIME);
}

tbe::TB_Time::TB_Time()
{
    currentFrame = 0.0;
    lastFrame = 0.0;
    deltaFrame = 0.0f;
}