//
// Created by movleaxedx on 8.10.19.
//


//todo uniforms / defines introspection

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>

#include <common/defines.hpp>
#include <scene/ogl_renderer/gl_helpers.hpp>
#include <assets/shader_program.hpp>
#include <scene/ogl_renderer/shader_program.hpp>
#include <iostream>

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
    GL_SAFE_CALL(glDeleteShader, m_name);
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


std::unique_ptr<engine::ogl::shader_program> engine::ogl::shader_program::from_program(const engine::shader_program& program)
{
    return std::make_unique<shader_program>(program.get_vertex_shader(), program.get_fragment_shader());
}


engine::ogl::shader_program::~shader_program()
{
    GL_SAFE_CALL(glDeleteProgram, m_name);
}


void engine::ogl::shader_program::bind()
{
    GL_SAFE_CALL(glUseProgram, m_name);
}


void engine::ogl::shader_program::unbind()
{
    GL_SAFE_CALL(glUseProgram, 0);
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
    if (matrix_uniform >= 0) {
        GL_SAFE_CALL(glUniformMatrix4fv, matrix_uniform, 1, GL_FALSE, glm::value_ptr(matrix));
        return;
    }

    assert(glGetError() == GL_NO_ERROR);

#ifdef __ENGINE_GL_UNIFORMS_DEBUG__
    std::cerr << "OPENGL ERROR::TRIED TO SET NOT DEFINED MATRIX 4 UNIFORM: " + name << std::endl;
#endif
}


engine::ogl::set_int_uniform::set_int_uniform(const std::string& name, uint32_t uniform)
    : m_name(name)
    , m_uniform(uniform)
{
}


void engine::ogl::set_int_uniform::execute(uint64_t program) const
{
    auto int_uniform = glGetUniformLocation(program, m_name.data());
    if (int_uniform >= 0) {
        GL_SAFE_CALL(glUniform1i, int_uniform, m_uniform);
        return;
    }

    assert(glGetError() == GL_NO_ERROR);

#ifdef __ENGINE_GL_UNIFORMS_DEBUG__
    std::cerr << "OPENGL ERROR::TRIED TO SET NOT DEFINED INT UNIFORM: " + m_name << std::endl;
#endif
}


engine::ogl::set_float_uniform_array::set_float_uniform_array(
    const std::string& name,
    const std::vector<engine::light_source>& light_sources)
    : m_name(name),
    m_light_sources_ref(light_sources)
{
}


void engine::ogl::set_float_uniform_array::execute(uint64_t program) const
{
    auto int_uniform = glGetUniformLocation(program, m_name.data());

    if (int_uniform >= 0) {
        std::vector<glm::vec3> light_positions;
        light_positions.reserve(m_light_sources_ref.size());

        //todo remove
        for (const auto& light_source : m_light_sources_ref) {
            light_positions.emplace_back(light_source.get_position());
        }

        GL_SAFE_CALL(glUniform3fv, int_uniform, light_positions.size(), glm::value_ptr(light_positions.front()));
        return;
    }

    assert(glGetError() == GL_NO_ERROR);

#ifdef __ENGINE_GL_UNIFORMS_DEBUG__
    std::cerr << "OPENGL ERROR::TRIED TO SET NOT DEFINED FLOAT ARRAY UNIFORM: " + m_name << std::endl;
#endif
}


engine::ogl::set_vec3_uniform::set_vec3_uniform(const std::string& name, glm::vec3 uniform)
    : m_name(name)
    , m_uniform(uniform)
{
}


void engine::ogl::set_vec3_uniform::execute(uint64_t program) const
{
    auto vector_uniform = glGetUniformLocation(program, m_name.c_str());

    if (vector_uniform >= 0) {
        GL_SAFE_CALL(glUniform3fv, vector_uniform, 1, glm::value_ptr(m_uniform));
        return;
    }

    assert(glGetError() == GL_NO_ERROR);

#ifdef __ENGINE_GL_UNIFORMS_DEBUG__
    std::cerr << "OPENGL ERROR::TRIED TO SET NOT DEFINED  VEC3 UNIFORM: " + m_name << std::endl;
#endif
}
