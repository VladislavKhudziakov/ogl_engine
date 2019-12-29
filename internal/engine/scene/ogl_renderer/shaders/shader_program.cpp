//
// Created by movleaxedx on 28.12.19.
//

#include <scene/ogl_renderer/shaders/shader_program.hpp>
#include <scene/ogl_renderer/shaders/shader.hpp>
#include <assets/shader_program.hpp>
#include <cassert>

constexpr int32_t MAX_LOG_BUFFER_SIZE = 1000;

std::unique_ptr<engine::ogl::shader_program>
engine::ogl::shader_program::from_program(const engine::shader_program& program)
{
    std::vector<shader> shaders;
    for (auto& shader : program.get_shaders()) {
        shader::type curr_type;

        switch (shader.type) {
        case engine::shader_program::shader_type::vertex:
            curr_type = shader::type::vertex;
            break;
        case engine::shader_program::shader_type::fragment:
            curr_type = shader::type::fragment;
            break;
        case engine::shader_program::shader_type::geometry:
            curr_type = shader::type::geometry;
            break;
        case engine::shader_program::shader_type::tessellation_control:
            curr_type = shader::type::tess_control;
            break;
        case engine::shader_program::shader_type::tessellation_evaluate:
            curr_type = shader::type::tess_evaluation;
            break;
        case engine::shader_program::shader_type::compute:
            curr_type = shader::type::compute;
            break;
        }

        shaders.emplace_back(shader.source, curr_type);
    }

    return std::make_unique<shader_program>(shaders);
}

engine::ogl::shader_program::shader_program(const std::vector<shader>& shaders)
    : m_name(glCreateProgram())
{
    for(const auto& shader : shaders) {
        glAttachShader(m_name, shader);
    }

    glLinkProgram(m_name);

    check_link_status(m_name);
}


engine::ogl::shader_program::shader_program(shader_program&& src) noexcept
    : m_name(0)
{
    *this = std::move(src);
}


engine::ogl::shader_program& engine::ogl::shader_program::operator=(shader_program&& src) noexcept
{
    assert(this != &src);

    m_name = src.m_name;
    src.m_name = 0;

    return *this;
}


engine::ogl::shader_program::operator GLuint() const
{
    return m_name;
}


engine::ogl::shader_program::~shader_program()
{
    glDeleteProgram(m_name);
}


void engine::ogl::shader_program::check_link_status(GLuint program)
{
    GLint link_status;

    glGetProgramiv(program, GL_LINK_STATUS, &link_status);

    if (link_status == GL_FALSE) {
        char log_buf[MAX_LOG_BUFFER_SIZE];
        int32_t log_size;
        glGetProgramInfoLog(program, MAX_LOG_BUFFER_SIZE, &log_size, log_buf);
        throw std::runtime_error("ERROR WHILE SHADERS LINK: " + std::string(log_buf));
    }
}
