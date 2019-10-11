//
// Created by Vladislav Khudiakov on 10/11/19.
//

#pragma once

#include <glm/glm.hpp>

namespace engine
{
    class camera
    {
    public:
        camera(const glm::vec3&, const glm::vec3&, float);
        void set_direction(glm::vec3);
        void set_position(glm::vec3);
        void set_fov(float);

        glm::vec3 get_position() const;
        glm::vec3 get_direction() const;
        float get_fov();

    private:
        glm::vec3 m_position;
        glm::vec3 m_look_direction;
        float m_fov;
    };
} // namespace engine
