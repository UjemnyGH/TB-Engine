#version 430 core

out vec4 oCol;
in vec2 tCoo;

uniform sampler2D tex;

void main()
{
    oCol = texture(tex, tCoo);
}