//
// Created by movleaxedx on 28.12.19.
//


#pragma once
#include <scene/ogl_renderer/shaders/shader.hpp>
#include <vector>
#include <stdexcept>
#include <memory>

namespace engine
{
    class shader_program;
}

namespace engine::ogl
{
    class shader_program
    {
    public:
        static std::unique_ptr<shader_program> from_program(const engine::shader_program&);

        explicit shader_program(const std::vector<shader>& shaders);
        ~shader_program();

        shader_program(const shader_program&) = delete;
        shader_program& operator=(const shader_program&) = delete;

        shader_program(shader_program&&) noexcept;
        shader_program& operator=(shader_program&&) noexcept;
        operator GLuint() const;

        template<typename visitor_t>
        void visit(const visitor_t& visitor) const
        {
            visitor.accept(const_cast<const shader_program&>(*this));
        }

    private:
        static void check_link_status(GLuint program);
        GLuint m_name;
    };
} // namespace engine::ogl
