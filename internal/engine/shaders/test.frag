#version 330 core

precision highp float;

out vec4 FragColor;
in vec3 color;

void main()
{
    FragColor = vec4(color, 1.0);
}