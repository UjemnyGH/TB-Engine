#pragma once
#include <glm/glm.hpp>

namespace tbeCam
{
    //Keyboard inputs
    void keyboard(unsigned char key, int x, int y);
    //Mouse buttons inputs
    void mouse(int stat, int key, int x, int y);
    //Get mouse motion
    void motion(int x, int y);
    //Set camera speed
    void setSpeed(float f_speed);
    //Set camera sensitivity
    void setSensitivity(float f_sensitivity);
    //Set centering mouse
    void setCenterMouse(bool f_centerMouse);
    //Centering mouse
    void f_centerMouse();

    //Get position of camera
    glm::vec3 getPosition();
    //Get rotation of camera
    glm::vec3 getRotation();
    //Get up vector
    glm::vec3 getUp();
}