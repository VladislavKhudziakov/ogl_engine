//
// Created by movleaxedx on 8.10.19.
//

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>

#include "shader_program.hpp"

engine::shader_program::shader::shader(const std::string& sources, engine::shader_program::shader_type type)
    : m_index(glCreateShader(type == shader_type::vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER))
{
    auto sources_ptr = sources.c_str();
    glShaderSource(m_index, 1, &sources_ptr, nullptr);
    glCompileShader(m_index);

    int32_t compile_status;
    glGetShaderiv(m_index, GL_COMPILE_STATUS, &compile_status);

    if (compile_status == GL_FALSE) {
        int32_t log_buffer_size;
        glGetShaderiv(m_index, GL_INFO_LOG_LENGTH, &log_buffer_size);
        char log_msg[log_buffer_size];
        glGetShaderInfoLog(m_index, log_buffer_size, &log_buffer_size, log_msg);
        throw std::logic_error(std::string("SHADER COMPILATION ERROR::") + log_msg);
    }
}


engine::shader_program::shader_program(
    const std::string& vertex_shader_source,
    const std::string& fragment_shader_source)
    : m_index(glCreateProgram())
    , m_vertex_shader(vertex_shader_source, shader_type::vertex)
    , m_fragment_shader(fragment_shader_source, shader_type::fragment)
{
    glAttachShader(m_index, m_vertex_shader.m_index);
    glAttachShader(m_index, m_fragment_shader.m_index);
    glLinkProgram(m_index);

    int32_t linking_status = 0;

    glGetProgramiv(m_index, GL_LINK_STATUS, &linking_status);

    if (linking_status == GL_FALSE) {
        int32_t log_buffer_size = 0;
        glGetProgramiv(m_index, GL_INFO_LOG_LENGTH, &log_buffer_size);
        char log_msg[log_buffer_size];
        glGetProgramInfoLog(m_index, log_buffer_size, &log_buffer_size, log_msg);
        throw std::logic_error(std::string("SHADER PROGRAM LINKING ERROR::") + log_msg);
    }
}


void engine::shader_program::bind()
{
    glUseProgram(m_index);
}


void engine::shader_program::unbind()
{
    glUseProgram(0);
}


void engine::shader_program::apply_uniform_command(const uniform_command& command)
{
    command.execute(m_index);
}


engine::set_mat4_uniform::set_mat4_uniform(const std::string& name, const glm::mat4& matrix)
    : name(name)
    , matrix(matrix)
{
}


void engine::set_mat4_uniform::execute(uint64_t program) const
{
    auto matrix_uniform = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(matrix_uniform, 1, GL_FALSE, glm::value_ptr(matrix));
}
