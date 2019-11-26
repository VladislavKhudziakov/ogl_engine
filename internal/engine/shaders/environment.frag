#version 330 core

precision highp float;

out vec4 FragColor;

in vec3 var_uv;

uniform samplerCube u_env;

void main()
{
    FragColor = texture(u_env, var_uv);
}