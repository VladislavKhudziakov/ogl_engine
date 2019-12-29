//
// Created by movleaxedx on 28.12.19.
//


#pragma once

#include <string>
#include <glad/glad.h>

namespace engine::ogl
{
    class shader
    {
    public:
        enum class type {
            vertex = GL_VERTEX_SHADER,
            fragment = GL_FRAGMENT_SHADER,
            geometry = GL_GEOMETRY_SHADER,
            tess_control = GL_TESS_CONTROL_SHADER,
            tess_evaluation = GL_TESS_EVALUATION_SHADER,
            compute = GL_COMPUTE_SHADER
        };

        shader(const std::string& source, type type);
        ~shader();
        shader(const shader&) = delete;
        shader& operator=(const shader&) = delete;
        shader(shader&&) noexcept;
        shader& operator=(shader&&) noexcept;
        operator GLuint() const;

    private:
        GLuint m_name;
    };
}

