#version 330 core

#define LIGHT_SOURCES_COUNT 2

precision highp float;

out vec4 FragColor;

in vec3 var_normal;
in vec2 var_uv;
in vec3 var_vertex;
in vec3 var_cam_pos;

uniform vec3 u_light_sources[LIGHT_SOURCES_COUNT];

uniform sampler2D u_texture;
uniform samplerCube u_env;

void main()
{
    vec4 texture_color = texture(u_texture, var_uv);

    vec3 I = normalize(var_vertex - var_cam_pos);
    vec3 R = reflect(I, normalize(var_normal));

    vec4 env_color = texture(u_env, R);
    vec3 light_vector;

    vec3 final_color = vec3(0.0);

    for (int i = 0; i < LIGHT_SOURCES_COUNT; ++i) {
        float n_dot_l = max(dot(normalize(u_light_sources[i] - var_vertex), normalize(var_normal)), 0);
        final_color += env_color.rgb * n_dot_l;
    }

    FragColor = vec4(final_color, texture_color.a);
}