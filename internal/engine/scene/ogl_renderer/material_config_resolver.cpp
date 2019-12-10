//
// Created by movleaxedx on 23.11.19.
//

#include <common/material_config.hpp>
#include <glad/glad.h>

#include <scene/ogl_renderer/material_config_resolver.hpp>

engine::material_config_resolver::material_config_resolver(const engine::material_config& cfg)
    : m_config_ref(cfg)
{
}

void engine::material_config_resolver::set_config()
{
    set_blending();
    set_culling();

    if (m_config_ref.enable_depth_test) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    if (m_config_ref.write_color) {
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    } else {
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    }
}

void engine::material_config_resolver::set_blending()
{
    switch (m_config_ref.culling) {
    case material_config::culling_type::none:
        glDisable(GL_CULL_FACE);
        break;
    case material_config::culling_type::front:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        break;
    case material_config::culling_type::back:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        break;
    }
}

void engine::material_config_resolver::set_culling()
{
    switch (m_config_ref.blending) {
    case material_config::blend_mode::none:
        glDisable(GL_BLEND);
        break;
    case material_config::blend_mode::alpha:
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        break;
    case material_config::blend_mode::add:
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        break;
    case material_config::blend_mode::multiply:
        glBlendFunc(GL_DST_COLOR, GL_ZERO);
        break;
    }
}
