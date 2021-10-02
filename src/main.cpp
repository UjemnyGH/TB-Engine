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
#include "shaders.h"
#include "buffers.h"
#include "cube.h"
#include "mesh.h"
#include "player/camera.h"
#include "TB_time.h"

const int cubeCount = 3;

tbe::Time gTime;
tbe::Cube ground;
tbe::Cube player;
tbe::Mesh mh[cubeCount];

float zNear = 0.001f;
float zFar = 10000.0f;

float deltaTime = 0.0f;
float lastTime = 0.0f;

glm::mat4x4 proj;
float scale = 1.0f;


float color[512] = {
    1.0f, 1.0f, 1.0f
};

float grassColor[24] = {
    0.0f, 0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
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
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutInitWindowSize(800, 600);

    glutCreateWindow("Window");

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        return -1;
    }

    if(!GLEW_VERSION_4_3)
    {
        return -2;
    }

    glGetError();

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
    glEnable(GL_DEPTH_TEST);

    for(int i = 0; i < cubeCount; i++)
    {
        mh[i].init("data/shaders/bfs.glsl", "data/shaders/bvs.glsl", "data/models/testLPBall2.obj", GL_DYNAMIC_DRAW, color, sizeof(color));
    }
    
    ground.init("data/shaders/bfs.glsl", "data/shaders/bvs.glsl", GL_DYNAMIC_DRAW, grassColor, sizeof(grassColor));

    player.init("data/shaders/bfs.glsl", "data/shaders/bvs.glsl", GL_DYNAMIC_DRAW, grassColor, sizeof(grassColor));
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

    for(int i = 0; i < cubeCount; i++)
    {
        mh[i].SetPosition(static_cast<float>(i * 3) - (cubeCount * 3) / 2, 1.0f, 0.0f);
        mh[i].SetColor(color, sizeof(color));
        
        mh[i].draw(pvm);
    }

    ground.SetScale(10.0f, 0.1f, 10.0f);

    ground.draw(pvm, GL_TRIANGLES);

    player.SetPositionScale(tbeCam::getPosition() - glm::vec3(0.0f, 1.0f, 0.0f), 0.5f, 2.0f, 0.5f);

    player.draw(pvm, GL_LINES);

    tbeCam::f_centerMouse();

    tbeCam::setSensitivity(0.1f);

    glutSwapBuffers();

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
    for(int i = 0; i < cubeCount; i++)
    {
        mh[i].deleteMesh();
    }

    ground.deleteCube();
    player.deleteCube();
}