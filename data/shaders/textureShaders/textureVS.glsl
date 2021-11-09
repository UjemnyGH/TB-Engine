#version 430 core

uniform mat4 pvm;

layout(location = 0)in vec4 iPos;
layout(location = 1)in vec2 Col;
layout(location = 2)in vec2 tCo;

out vec4 ioCol;
out vec2 tCoo;

void main()
{
    gl_Position = pvm * iPos;
    tCoo = tCo;
}