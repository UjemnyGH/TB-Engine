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
#include "mesh.h"

//Cube cb;
Mesh mh;

float zNear = 0.001f, zFar = 1000.0f;

glm::vec3 pos = glm::vec3(0.0f, 0.0f, -3.0f);
glm::vec3 rot;
glm::mat4x4 proj;

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        pos.y += 0.3f;
        break;
    
    case 's':
        pos.y -= 0.3f;
        break;

    case 'a':
        pos.x -= 0.3f;
        break;

    case 'd':
        pos.x += 0.3f;
        break;
    }
}

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

    glutKeyboardFunc(keyboard);

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

    //cb.init("data/shaders/bfs.glsl", "data/shaders/bvs.glsl", GL_DYNAMIC_DRAW, color, sizeof(color));

    mh.init("data/shaders/bfs.glsl", "data/shaders/bvs.glsl", "data/models/testCube.obj", GL_DYNAMIC_DRAW, color, sizeof(color));
}

void DisplayScene()
{
    glm::mat4x4 vi = glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), rot, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4x4 mod = glm::mat4x4(1.0);

    mod = glm::rotate(mod, pos.y, glm::vec3(0.0f, 1.0f, 0.0f));
    mod = glm::rotate(mod, pos.x, glm::vec3(1.0f, 0.0f, 0.0f));

    glClearColor(0.2f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4x4 pvm = proj * vi * mod;

    std::random_device rd;

    for(int i = 0; i < 8; i++)
    {
        color[i] = (rd() % 100) / 100.0f;
    }

    //cb.SetColor(color, sizeof(color));

    //cb.draw(pvm);

    mh.draw(pvm);

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
    //cb.deleteCube();
    mh.deleteMesh();
}