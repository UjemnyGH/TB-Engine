#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>
#include <random>
#include <future>
#include <math.h>
#include "TB_shaders.h"
#include "TB_buffers.h"
#include "TB_cube.h"
#include "TB_mesh.h"
#include "player/TB_camera.h"
#include "TB_time.h"
#include "TB_window.h"

tbe::Time gTime;
tbe::Window gameWindow;

float zNear = 0.001f;
float zFar = 10000.0f;

glm::mat4x4 proj;

double planetsPos;
double planets2Pos;
tbe::Cube planet;
tbe::Cube planet2;
tbe::Cube sun;

float color[512] = {
    1.0f, 1.0f, 1.0f
};

float planet1col[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f
};

float planet2col[] = {
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f
};

float suncol[] = {
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};

void InitScene();
void DisplayScene();
void ReshapeScene(int w, int h);
void DeleteScene();

void mainLoop()
{
    glutKeyboardFunc(tbeCam::keyboard);
    glutMouseFunc(tbeCam::mouse);
    glutPassiveMotionFunc(tbeCam::motion);

    while (true)
    {
        std::random_device rd;

        for(int i = 0; i < 512; i++)
        {
            color[i] = (rd() % 100) / 100.0f;
        }
    }
}

int main(int argc, char** argv)
{
    gameWindow = tbe::Window(argc, argv, "Game");

    InitScene();

    std::future<void> mainLoopThread = std::async(mainLoop);

    glutDisplayFunc(DisplayScene);
    glutReshapeFunc(ReshapeScene);
    
    glutMainLoop();

    DeleteScene();

    return 0;
}

void InitScene()
{
    planet.init(tbe::colorFS, tbe::colorVS, GL_DYNAMIC_DRAW, planet1col, sizeof(planet1col));
    planet2.init(tbe::colorFS, tbe::colorVS, GL_DYNAMIC_DRAW, planet2col, sizeof(planet2col));
    sun.init(tbe::colorFS, tbe::colorVS, GL_DYNAMIC_DRAW, suncol, sizeof(suncol));
}

void DisplayScene()
{
    tbeCam::setSpeed(0.05f * gTime.deltaTime());

    glm::mat4x4 vi = glm::mat4x4(1.0);

    vi = glm::lookAt(tbeCam::getPosition(), tbeCam::getRotation(), tbeCam::getUp());

    glm::mat4x4 mod = glm::mat4x4(1.0);

    glClearColor(0.2f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4x4 pvm = proj * vi * mod;

    planetsPos += 0.01;
    planets2Pos += 0.05;

    planet.SetPositionScale(glm::vec3((cos(planetsPos) - sin(planetsPos)) * 2.0f, 0.0f, (cos(planetsPos) + sin(planetsPos)) * 2.0f), 1.0f);
    planet.draw(pvm, GL_TRIANGLES);

    planet2.SetPositionScale(glm::vec3((cos(planets2Pos) - sin(planets2Pos)) + planet.GetPosition().x * 2.0f, 0.0f, (cos(planets2Pos) + sin(planets2Pos)) + planet.GetPosition().z * 2.0f), 1.0f);
    planet2.draw(pvm, GL_TRIANGLES);

    sun.draw(pvm, GL_TRIANGLES);

    tbeCam::f_centerMouse();
    tbeCam::setSensitivity(0.1f);

    glutSwapBuffers();

    gameWindow.basicErrorChecking();

    glutPostRedisplay();
}

void ReshapeScene(int w, int h)
{
    glViewport(0, 0, w, h);

    float fov = 70.0f;

    proj = glm::perspectiveFov(fov, static_cast<float>(w), static_cast<float>(h), zNear, zFar);
}

void DeleteScene()
{

}