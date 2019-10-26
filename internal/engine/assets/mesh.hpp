//
// Created by movleaxedx on 13.10.19.
//


#pragma once
#include <memory>
#include <string>

#include <glm/mat4x4.hpp>

#include <geometry.hpp>
#include <material.hpp>

namespace engine
{
    class mesh
    {
    public:
        mesh() = default;
        ~mesh() = default;

        explicit mesh(std::string, std::shared_ptr<interfaces::geometry_buffer>, std::shared_ptr<material> material = nullptr);
        std::shared_ptr<interfaces::geometry_buffer> get_geometry();
        void set_geometry(std::shared_ptr<geometry>);
        void attach_material(std::shared_ptr<material>);

        void set_transformation(glm::mat4);
        glm::mat4 get_transformation() const;

        std::string get_name() const;

        void draw();

    private:
        std::shared_ptr<interfaces::geometry_buffer> m_geometry;
        std::shared_ptr<material> m_material;
        std::string m_name;
        glm::mat4 m_transformation_matrix { 1 };
    };
} // namespace engine
