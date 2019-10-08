#version 330 core

precision highp float;

layout (location = 0) in vec3 a_vertex;
layout (location = 1) in vec2 a_uv;
layout (location = 2) in vec3 a_normal;

out vec3 color;

void main()
{
    gl_Position = vec4(a_vertex, 1);
    color = a_normal;
}