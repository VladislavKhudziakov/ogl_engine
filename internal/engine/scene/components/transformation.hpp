//
// Created by movleaxedx on 20.10.19.
//


#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace engine
{
    struct transformation
    {
    public:
        transformation(glm::vec3, glm::vec3, glm::vec3);
        transformation() = default;
        ~transformation() = default;

        glm::mat4 calculate() const;

        glm::vec3 translation {0, 0, 0};
        glm::vec3 scale {1, 1, 1};
        glm::vec3 rotation {0, 0, 0};
    };
}

