//
// Created by movleaxedx on 8.10.19.
//


#include <shader_program.hpp>


engine::shader_program::shader_program(const std::string& name, std::string& vs, std::string& fs)
    : m_name(name)
    , m_vertex_shader(std::move(vs))
    , m_fragment_shader(std::move(fs))
{
}


engine::shader_program::shader_program(const std::string& name, std::string&& vs, std::string&& fs)
    : m_name(name)
    , m_vertex_shader(std::move(vs))
    , m_fragment_shader(std::move(fs))
{
}


const std::string& engine::shader_program::get_name() const
{
    return m_name;
}


const std::string& engine::shader_program::get_vertex_shader() const
{
    return m_vertex_shader;
}


const std::string& engine::shader_program::get_fragment_shader() const
{
    return m_fragment_shader;
}


void engine::shader_program::clear()
{
    m_vertex_shader = std::move(std::string());
    m_fragment_shader = std::move(std::string());
}
