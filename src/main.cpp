#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <random>
#include <future>
#include "shaders.h"
#include "buffers.h"
#include "cube.h"
#include "mesh.h"

const int cubeCount = 3;

Cube ground;
//Cube cb[cubeCount];
Mesh mh[cubeCount];

float zNear = 0.001f;
float zFar = 10000.0f;

glm::vec3 pos = glm::vec3(0.0f, 0.0f, -3.0f);
glm::vec3 rot;
glm::mat4x4 proj;
float scale = 1.0f;

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        pos.y += 0.1f;
        break;
    
    case 's':
        pos.y -= 0.1f;
        break;

    case 'a':
        pos.x -= 0.1f;
        break;

    case 'd':
        pos.x += 0.1f;
        break;

    case '+':
        scale += 0.01f;
        break;

    case '-':
        scale -= 0.01f;
        break;
    }
}

float color[512] = {
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
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

    glutKeyboardFunc(keyboard);

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
        //cb[i].init("data/shaders/bfs.glsl", "data/shaders/bvs.glsl", GL_DYNAMIC_DRAW, color, sizeof(color));
        mh[i].init("data/shaders/bfs.glsl", "data/shaders/bvs.glsl", "data/models/testLPBall2.obj", GL_DYNAMIC_DRAW, color, sizeof(color));
        ground.init("data/shaders/bfs.glsl", "data/shaders/bvs.glsl", GL_DYNAMIC_DRAW, grassColor, sizeof(grassColor));
    }

}

void DisplayScene()
{
    glm::mat4x4 vi = glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), rot, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4x4 mod = glm::mat4x4(1.0);

    mod = glm::rotate(mod, pos.y, glm::vec3(0.0f, 1.0f, 0.0f));
    mod = glm::rotate(mod, pos.x, glm::vec3(1.0f, 0.0f, 0.0f));

    mod = glm::scale(mod, glm::vec3(scale, scale, scale));

    glClearColor(0.2f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4x4 pvm = proj * vi * mod;

    for(int i = 0; i < cubeCount; i++)
    {
        //cb[i].SetPosition(static_cast<float>(i * 3) - (cubeCount * 3) / 2, 0.0f, 0.0f);
        //cb[i].SetColor(color, sizeof(color));

        //cb[i].draw(pvm);

        mh[i].SetPosition(static_cast<float>(i * 3) - (cubeCount * 3) / 2, 1.0f, 0.0f);
        mh[i].SetColor(color, sizeof(color));
        
        mh[i].draw(pvm);
    }

    ground.SetScale(10.0f, 0.1f, 10.0f);

    ground.draw(pvm);


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
        //cb[i].deleteCube();
        mh[i].deleteMesh();
    }
}