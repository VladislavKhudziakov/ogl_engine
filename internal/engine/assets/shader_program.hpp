//
// Created by movleaxedx on 8.10.19.
//

#pragma once

#include <glm/glm.hpp>
#include <string>

namespace engine
{
    class shader_program
    {
    public:
        shader_program(const std::string&, std::string&, std::string&);
        shader_program(const std::string&, std::string&&, std::string&&);

        ~shader_program() = default;

        const std::string& get_name() const;
        const std::string& get_vertex_shader() const;
        const std::string& get_fragment_shader() const;
        void clear();

    private:
        std::string m_name;
        std::string m_vertex_shader;
        std::string m_fragment_shader;
    };
} // namespace engine
