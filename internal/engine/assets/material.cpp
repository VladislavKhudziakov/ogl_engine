//
// Created by Vladislav Khudiakov on 10/15/19.
//

#include <string>

#include <assets/material.hpp>
#include <assets/shader_program.hpp>


engine::material::material(std::shared_ptr<engine::shader_program> shader)
    : m_shader(std::move(shader))
{
}


std::shared_ptr<engine::interfaces::texture> engine::material::get_texture(const std::string& name) const
{
    return m_textures.at(name);
}


void engine::material::set_texture(const std::string& name, const assets::texture_t& texture)
{
    m_textures.emplace(name, texture);
}


const engine::assets::shader_program_t& engine::material::get_shader() const
{
    return m_shader;
}


void engine::material::set_shader(const assets::shader_program_t& shader)
{
    m_shader = shader;
}


const engine::material::material_textures_t& engine::material::get_textures() const
{
    return m_textures;
}


void engine::material::set_rendering_config(const engine::material_config& config)
{
    m_config = config;
}


const engine::material_config& engine::material::get_config() const
{
    return m_config;
}
