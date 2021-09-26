#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <random>
#include "shaders.h"
#include "buffers.h"
#include "cube.h"

Cube cb[2];

float zNear = 0.001f, zFar = 1000.0f;

glm::vec3 pos = glm::vec3(0.0f, 0.0f, -3.0f);
glm::vec3 rot;
glm::mat4x4 proj;

float vertices[24] = {
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f
};

unsigned int indices[36] = {
    0, 1, 2,
    1, 2, 3,
    4, 5, 6,
    5, 6, 7,
    0, 2, 4,
    2, 4, 6,
    1, 3, 5,
    3, 5, 7,
    0, 1, 4,
    1, 4, 5,
    2, 3, 6,
    3, 6, 7
};

float color[24] = {
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f
};

float color2[24] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};

void InitScene();
void DisplayScene();
void ReshapeScene(int w, int h);
void DeleteScene();

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

    glutDisplayFunc(DisplayScene);
    glutReshapeFunc(ReshapeScene);
    
    glutMainLoop();

    DeleteScene();

    return 0;
}

void InitScene()
{
    glEnable(GL_DEPTH_TEST);

    cb[0].init("data/shaders/bfs.glsl", "data/shaders/bvs.glsl", GL_DYNAMIC_DRAW, color, sizeof(color));
    cb[1].init("data/shaders/bfs.glsl", "data/shaders/bvs.glsl", GL_DYNAMIC_DRAW, color2, sizeof(color2));
}

void DisplayScene()
{
    glm::mat4x4 vi = glm::lookAt(pos, rot, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4x4 mod = glm::mat4x4(1.0);

    glClearColor(0.2f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4x4 pvm = proj * vi * mod;

    cb[0].SetScale(0.5f, 0.5f, 0.5f);

    cb[0].draw(pvm);
    cb[1].draw(pvm);

    glutSwapBuffers();

    glutPostRedisplay();
}

void ReshapeScene(int w, int h)
{
    glViewport(0, 0, w, h);

    float aspect = 1.0f;
    float fovy = 10.0f;

    if(h > 0)
    {
        aspect = w / static_cast<float>(h);
    }

    proj = glm::perspective(fovy, aspect, zNear, zFar);
}

void DeleteScene()
{
    cb[0].deleteCube();
    cb[1].deleteCube();
}