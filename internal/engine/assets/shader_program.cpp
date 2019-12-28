//
// Created by movleaxedx on 8.10.19.
//


#include <shader_program.hpp>

engine::shader_program::shader_program(const std::string& name, std::vector<shader>&& shaders)
    : m_name(name)
    , m_shaders(std::move(shaders))
{
}

engine::shader_program::shader_program(const std::string& name, std::vector<shader>& shaders)
    : m_name(name)
    , m_shaders(std::move(shaders))
{
}


const std::string engine::shader_program::get_name() const
{
    return m_name;
}


void engine::shader_program::clear()
{
    m_vertex_shader = std::move(std::string());
    m_fragment_shader = std::move(std::string());
}


const std::vector<engine::shader_program::shader>& engine::shader_program::get_shaders() const
{
    return m_shaders;
}


std::vector<engine::shader_program::shader>& engine::shader_program::get_shaders()
{
    return m_shaders;
}
