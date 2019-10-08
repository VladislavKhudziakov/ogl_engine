#version 330 core

precision highp float;

layout (location = 1) in vec3 a_vertex;

void main()
{
    gl_Position = vec4(a_vertex, 1);
}