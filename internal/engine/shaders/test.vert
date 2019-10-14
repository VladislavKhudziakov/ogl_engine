#version 330 core

precision highp float;

layout(location = 0) in vec3 a_vertex;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec3 a_normal;

uniform mat4 u_mvp;

out vec3 color;
out vec2 var_uv;

void main()
{
    gl_Position = u_mvp * vec4(a_vertex, 1);
    color = a_normal;
    var_uv = a_uv;
}