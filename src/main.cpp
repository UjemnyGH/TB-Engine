#include "TB_Engine.h"

tbe::Time gTime;
tbe::Window gameWindow;

tbe::Cube cube;

float zNear = 0.001f;
float zFar = 10000.0f;

glm::mat4x4 proj;

float color[512] = {
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f
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
    cube.init(tbe::textureFS, tbe::textureVS, "data/textures/textureTest.png", GL_DYNAMIC_DRAW, color, sizeof(color));
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

    cube.draw(pvm, GL_TRIANGLES);

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
    cube.deleteCube();
}