#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include "TB_camera.h"
#include "../TB_time.h"

int bX, bY;
bool centerMouse = true;
float yaw, pitch;
float lastX = 400, lastY = 300;
float speed = 0.05f;
float sensitivity = 0.01f;

glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

void tbeCam::keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        camPos += camFront * speed;
        break;
    
    case 's':
        camPos -= camFront * speed;
        break;

    case 'a':
        camPos -= glm::normalize(glm::cross(camFront, camUp)) * speed;
        break;

    case 'd':
        camPos += glm::normalize(glm::cross(camFront, camUp)) * speed;
        break;

    case ' ':
        camPos.y += 0.1f * speed;
        break;

    case 'c':
        camPos.y -= 0.1f * speed;
        break;

    case 'b':
        if(centerMouse)
        {
            centerMouse = false;
        }
        else
        {
            centerMouse = true;
        }
        break;
    }
}

void tbeCam::mouse(int stat, int key, int x, int y)
{
    bX = x;
    bY = y;
}

void tbeCam::motion(int x, int y)
{
    glm::vec3 direction;

    float xOff = x - lastX;
    float yOff = lastY - y;

    if(centerMouse)
    {
        lastX = glutGet(GLUT_WINDOW_WIDTH) / 2;
        lastY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

        bX = bY = 0.0f;

        lastX += bX;
        lastY += bY;

        if(x > glutGet(GLUT_WINDOW_WIDTH) / 2)
        {
            bX = bX - 1.0f;
        }
        else if(x < glutGet(GLUT_WINDOW_WIDTH) / 2)
        {
            bX = bX + 1.0f;
        }

        if(y > glutGet(GLUT_WINDOW_HEIGHT) / 2)
        {
            bY = bY - 1.0f;
        }
        else if(y < glutGet(GLUT_WINDOW_HEIGHT) / 2)
        {
            bY = bY + 1.0f;
        }

        setSensitivity(0.1f);
    }
    else
    {
        lastX = lastY = 0.0f;

        lastX = bX;
        lastY = bY;

        bX = x;
        bY = y;

        setSensitivity(0.0f);
    }

    xOff *= sensitivity;
    yOff *= sensitivity;

    yaw += xOff;
    pitch += yOff;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camFront = glm::normalize(direction);

    glutPostRedisplay();
}

void tbeCam::setSpeed(float f_speed)
{
    speed = f_speed;
}

void tbeCam::setSensitivity(float f_sensitivity)
{
    sensitivity = f_sensitivity;
}

void tbeCam::setCenterMouse(bool f_centerMouse)
{
    centerMouse = f_centerMouse;
}

void tbeCam::f_centerMouse()
{
    if(centerMouse)
    {
        glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    }
}

glm::vec3 tbeCam::getPosition()
{
    return camPos;
}

glm::vec3 tbeCam::getRotation()
{
    return camPos + camFront;
}

glm::vec3 tbeCam::getUp()
{
    return camUp;
}