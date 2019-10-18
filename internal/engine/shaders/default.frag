#version 330 core

precision highp float;

out vec4 FragColor;
in vec3 color;
in vec2 var_uv;

uniform sampler2D u_texture;

void main()
{
    vec4 texture_color = texture(u_texture, var_uv);
    FragColor = vec4(texture_color.rgb, 1.0);
}