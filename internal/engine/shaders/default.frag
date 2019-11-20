#version 330 core

#define LIGHT_SOURCES_COUNT 2

precision highp float;

//const vec3 light_position = vec3(30., 30., -30.);

out vec4 FragColor;

in vec3 var_normal;
in vec2 var_uv;
in vec3 var_vertex;

uniform vec3 u_light_sources[LIGHT_SOURCES_COUNT];

uniform sampler2D u_texture;

void main()
{
    vec4 texture_color = texture(u_texture, var_uv);
    vec3 light_vector;

    vec3 final_color = vec3(0.0);

    for (int i = 0; i < LIGHT_SOURCES_COUNT; ++i) {
        float n_dot_l = max(dot(normalize(u_light_sources[i] - var_vertex), normalize(var_normal)), 0);
        final_color += texture_color.rgb * n_dot_l;
    }

    FragColor = vec4(final_color, texture_color.a);
}