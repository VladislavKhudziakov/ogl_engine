//
// Created by movleaxedx on 3.11.19.
//


#pragma once

#include <glm/vec3.hpp>

namespace engine
{
    class light_source
    {
    public:
        light_source(const glm::vec3&, const glm::vec3&);
        ~light_source() = default;
        void set_position(const glm::vec3&);
        void set_color(const glm::vec3&);
        const glm::vec3& get_position() const;
        const glm::vec3& get_color() const;
    private:
        glm::vec3 m_position;
        glm::vec3 m_color;
    };
}

