//
// Created by movleaxedx on 8.10.19.
//

#pragma once

#include <glm/glm.hpp>
#include <string>

namespace engine::ogl
{
    class shader_program
    {
    public:
        struct uniform_command
        {
            friend shader_program;
            virtual ~uniform_command() = default;

        protected:
            virtual void execute(uint64_t) const = 0;
        };

        shader_program(const std::string&, const std::string&);
        ~shader_program();

        void bind();
        void unbind();

        void apply_uniform_command(const uniform_command&);

        enum class shader_type
        {
            vertex,
            fragment
        };

        struct shader
        {
            friend class shader_program;
            shader(const std::string&, shader_type);
            ~shader();

        private:
            uint64_t m_name;
        };

    private:
        uint64_t m_name;
        shader m_vertex_shader;
        shader m_fragment_shader;
    };

    struct set_mat4_uniform : shader_program::uniform_command
    {
        set_mat4_uniform(const std::string&, const glm::mat4&);
        void execute(uint64_t) const override;
        ~set_mat4_uniform() override = default;

    private:
        std::string name;
        glm::mat4 matrix;
    };


    struct set_int_uniform : shader_program::uniform_command
    {
        set_int_uniform(const std::string&, uint32_t);
        void execute(uint64_t) const override;
        ~set_int_uniform() override = default;

    private:
        std::string m_name;
        int32_t m_uniform;
    };
} // namespace engine
