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


void engine::material::bind()
{
    uint32_t curr_slot = 0;

    m_shader->bind();
    for (auto [name, texture] : m_textures) {
        texture->bind(curr_slot);
        m_shader->apply_uniform_command(engine::set_int_uniform(name, curr_slot));
        ++curr_slot;
    }
}


void engine::material::unbind()
{
    m_shader->unbind();
    for (auto [name, texture] : m_textures) {
        texture->unbind();
    }
}
