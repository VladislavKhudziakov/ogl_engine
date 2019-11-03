#version 330 core

precision highp float;

const vec3 light_position = vec3(30., 30., -30.);

out vec4 FragColor;

in vec3 var_normal;
in vec2 var_uv;
in vec3 var_vertex;


uniform sampler2D u_texture;

void main()
{
    vec4 texture_color = texture(u_texture, var_uv);
    vec3 light_vector;
    float n_dot_l = dot(normalize(light_position - var_vertex), normalize(var_normal));
    FragColor = vec4(texture_color.rgb * n_dot_l, texture_color.a);
}