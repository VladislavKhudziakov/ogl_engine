//
// Created by Vladislav Khudiakov on 10/11/19.
//

#pragma once

#include <mesh_instance.hpp>
#include <shader_program.hpp>
#include <glm/glm.hpp>

namespace engine
{
    struct scene_object
    {
        scene_object(std::shared_ptr<mesh_instance> mesh, const shader_program& program);
        std::shared_ptr<mesh_instance> m_mesh;
        shader_program program;
        void draw(glm::mat4);
    };
} // namespace engine
