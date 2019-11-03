#version 330 core

precision highp float;

layout(location = 0) in vec3 a_vertex;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec3 a_normal;

uniform mat4 u_mvp;
uniform mat4 u_mv;
uniform mat4 u_it_model;

out vec2 var_uv;
out vec3 var_normal;
out vec3 var_vertex;

void main()
{
    gl_Position = u_mvp * vec4(a_vertex, 1);
    var_uv = a_uv;
    var_normal = vec3(u_it_model * vec4(a_normal, 1.0));
    var_vertex = a_vertex;
}