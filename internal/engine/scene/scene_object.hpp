//
// Created by Vladislav Khudiakov on 10/11/19.
//

#pragma once

#include <memory>

#include <mesh_instance.hpp>
#include <material.hpp>
#include <shader_program.hpp>
#include <glm/glm.hpp>

namespace engine
{
    struct scene_object
    {
        scene_object(std::shared_ptr<mesh_instance>, std::shared_ptr<material>);
        std::shared_ptr<mesh_instance> m_mesh;
        std::shared_ptr<material> m_material;
        void draw(glm::mat4);
    };
} // namespace engine
