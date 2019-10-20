//
// Created by movleaxedx on 20.10.19.
//


#pragma once

#include <scene_object.hpp>
#include <mesh_instance.hpp>
#include <material.hpp>


namespace engine
{
    class object3d : public scene_object
    {
    public:
        object3d(const std::string& name, std::shared_ptr<mesh_instance>, std::shared_ptr<material>);
        ~object3d() override = default;

        void draw(glm::mat4 mat4) const override;

    private:
        std::shared_ptr<mesh_instance> m_mesh_instance;
        std::shared_ptr<material> m_material;
    };
}

