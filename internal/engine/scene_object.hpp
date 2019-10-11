//
// Created by Vladislav Khudiakov on 10/11/19.
//

#pragma once

#include <mesh.hpp>
#include <shader_program.hpp>
#include <glm/glm.hpp>

namespace engine
{
    struct scene_object
    {
        scene_object(std::unique_ptr<engine::mesh> mesh, const shader_program& program);
        std::unique_ptr<mesh> mesh;
        shader_program program;
        void draw(glm::mat4);
    };
} // namespace engine
