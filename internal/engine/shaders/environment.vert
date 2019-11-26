#version 330 core

precision highp float;
layout(location = 0) in vec3 a_vertex;

uniform mat4 u_mvp;
out vec3 var_uv;
uniform mat4 u_mv;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
    var_uv = a_vertex;
    vec4 pos = u_mvp * vec4(a_vertex, 1.0);
    gl_Position = pos;
}