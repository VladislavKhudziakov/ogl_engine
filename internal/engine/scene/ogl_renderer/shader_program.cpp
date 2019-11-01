//
// Created by movleaxedx on 8.10.19.
//

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>

#include <assets/shader_program.hpp>
#include <scene/ogl_renderer/shader_program.hpp>

engine::ogl::shader_program::shader::shader(const std::string& sources, shader_type type)
    : m_name(glCreateShader(type == shader_type::vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER))
{
    auto sources_ptr = sources.c_str();
    glShaderSource(m_name, 1, &sources_ptr, nullptr);
    glCompileShader(m_name);

    int32_t compile_status;
    glGetShaderiv(m_name, GL_COMPILE_STATUS, &compile_status);

    if (compile_status == GL_FALSE) {
        int32_t log_buffer_size;
        glGetShaderiv(m_name, GL_INFO_LOG_LENGTH, &log_buffer_size);
        char log_msg[log_buffer_size];
        glGetShaderInfoLog(m_name, log_buffer_size, &log_buffer_size, log_msg);
        throw std::logic_error(std::string("SHADER COMPILATION ERROR::") + log_msg);
    }
}


engine::ogl::shader_program::shader::~shader()
{
    glDeleteShader(m_name);
}


engine::ogl::shader_program::shader_program(
    const std::string& vertex_shader_source,
    const std::string& fragment_shader_source)
    : m_name(glCreateProgram())
    , m_vertex_shader(vertex_shader_source, shader_type::vertex)
    , m_fragment_shader(fragment_shader_source, shader_type::fragment)
{
    glAttachShader(m_name, m_vertex_shader.m_name);
    glAttachShader(m_name, m_fragment_shader.m_name);
    glLinkProgram(m_name);

    int32_t linking_status = 0;

    glGetProgramiv(m_name, GL_LINK_STATUS, &linking_status);

    if (linking_status == GL_FALSE) {
        int32_t log_buffer_size = 0;
        glGetProgramiv(m_name, GL_INFO_LOG_LENGTH, &log_buffer_size);
        char log_msg[log_buffer_size];
        glGetProgramInfoLog(m_name, log_buffer_size, &log_buffer_size, log_msg);
        throw std::logic_error(std::string("SHADER PROGRAM LINKING ERROR::") + log_msg);
    }
}


std::shared_ptr<engine::ogl::shader_program> engine::ogl::shader_program::from_program(const engine::shader_program& program)
{
    return std::make_shared<shader_program>(program.get_vertex_shader(), program.get_fragment_shader());
}


engine::ogl::shader_program::~shader_program()
{
    glDeleteProgram(m_name);
}


void engine::ogl::shader_program::bind()
{
    glUseProgram(m_name);
}


void engine::ogl::shader_program::unbind()
{
    glUseProgram(0);
}


void engine::ogl::shader_program::apply_uniform_command(const uniform_command& command)
{
    command.execute(m_name);
}


engine::ogl::set_mat4_uniform::set_mat4_uniform(const std::string& name, const glm::mat4& matrix)
    : name(name)
    , matrix(matrix)
{
}


void engine::ogl::set_mat4_uniform::execute(uint64_t program) const
{
    auto matrix_uniform = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(matrix_uniform, 1, GL_FALSE, glm::value_ptr(matrix));
}


engine::ogl::set_int_uniform::set_int_uniform(const std::string& name, uint32_t uniform)
    : m_name(name)
    , m_uniform(uniform)
{
}


void engine::ogl::set_int_uniform::execute(uint64_t program) const
{
    auto int_uniform = glGetUniformLocation(program, m_name.c_str());
    glUniform1i(int_uniform, m_uniform);
}