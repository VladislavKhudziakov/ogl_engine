//
// Created by Vladislav Khudiakov on 10/15/19.
//

#include <string>

#include <material.hpp>
#include <common/bind_context.hpp>


engine::material::material(std::shared_ptr<engine::shader_program> shader)
    : m_shader(std::move(shader))
{
}


std::shared_ptr<engine::interfaces::texture> engine::material::get_texture(const std::string& name) const
{
    return m_textures.at(name);
}


void engine::material::set_texture(const std::string& name, std::shared_ptr<interfaces::texture> texture)
{
    m_textures.emplace(name, texture);
}


std::shared_ptr<engine::shader_program> engine::material::get_shader() const
{
    return m_shader;
}


void engine::material::set_shader(std::shared_ptr<engine::shader_program> shader)
{
    m_shader = std::move(shader);
}


const engine::material::material_textures& engine::material::get_textures() const
{
    return m_textures;
}
