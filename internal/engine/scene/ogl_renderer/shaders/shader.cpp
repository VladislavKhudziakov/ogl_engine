//
// Created by movleaxedx on 28.12.19.
//

#include <scene/ogl_renderer/shaders/shader.hpp>

#include <stdexcept>
#include <cassert>

constexpr int32_t MAX_LOG_BUFFER_SIZE = 1000;


engine::ogl::shader::shader(const std::string& source, engine::ogl::shader::type type)
    : m_name{glCreateShader(GLenum(type))}
{
    if (m_name == 0) {
        throw std::runtime_error("ERROR WHILE SHADER CREATING");
    }

    auto source_data_ptr = source.data();
    glShaderSource(m_name, 1, &source_data_ptr, nullptr);
    glCompileShader(m_name);

    GLint compile_status;

    glGetShaderiv(m_name, GL_COMPILE_STATUS, &compile_status);

    if (compile_status == GL_FALSE) {
        char log_buffer[MAX_LOG_BUFFER_SIZE];
        GLint log_buffer_size;
        glGetShaderInfoLog(m_name, MAX_LOG_BUFFER_SIZE, &log_buffer_size, log_buffer);
        throw std::runtime_error("ERROR IN SHADER COMPILATION :" + std::string(log_buffer));
    }
}


engine::ogl::shader::~shader()
{
    glDeleteShader(m_name);
}


engine::ogl::shader::shader(engine::ogl::shader&& src) noexcept
    : m_name(0)
{
    *this = std::move(src);
}


engine::ogl::shader& engine::ogl::shader::operator=(engine::ogl::shader&& src) noexcept
{
    assert(this != &src);

    m_name = src.m_name;
    src.m_name = 0;
    return *this;
}


engine::ogl::shader::operator GLuint() const
{
    return m_name;
}
