//
// Created by movleaxedx on 8.10.19.
//

#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace engine
{
    class shader_program
    {
    public:
        enum class shader_type
        {
            vertex,
            fragment,
            geometry,
            tessellation_control,
            tessellation_evaluate,
            compute
        };

        struct shader
        {
            shader_type type;
            std::string source;
        };

        shader_program(const std::string&, std::vector<shader>&&);
        shader_program(const std::string&, std::vector<shader>&);
        ~shader_program() = default;

        const std::string& get_name() const;
        const std::vector<shader>& get_shaders() const;
        std::vector<shader>& get_shaders();

        void clear();

    private:
        std::string m_name;
        std::vector<shader> m_shaders;
        std::string m_vertex_shader;
        std::string m_fragment_shader;
    };
} // namespace engine
