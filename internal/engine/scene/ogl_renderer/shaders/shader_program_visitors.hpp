//
// Created by movleaxedx on 28.12.19.
//


#pragma once
#include <glad/glad.h>
#include <functional>
#include <scene/ogl_renderer/shaders/shader_program.hpp>

namespace engine::ogl
{
    template <typename callable_t>
    struct uniform_visitor
    {
    public:
        explicit uniform_visitor(callable_t callback, const std::string& uniform_name)
            : m_uniform_name(uniform_name)
            , m_uniform_callback(callback)
        {
        }

        virtual ~uniform_visitor() = default;

        void accept(const shader_program& program) const
        {
#ifdef __ENGINE__GL_DEBUG__
            if (glIsProgram(program) == GL_FALSE) {
                throw std::runtime_error("ERROR: TRIED TO USE INVALID PROGRAM");
            }
#endif

            auto location = glGetUniformLocation(program, m_uniform_name.data());

#ifdef __ENGINE__GL_DEBUG__
            if (location < 0) {
                std::cerr << "WARNING: TRIED TO USE UNDEFINED UNIFORM" << std::endl;
            }
#endif

            m_uniform_callback(location);
        }

    protected:
        std::string m_uniform_name;
        callable_t m_uniform_callback;
    };
} // namespace engine::ogl
