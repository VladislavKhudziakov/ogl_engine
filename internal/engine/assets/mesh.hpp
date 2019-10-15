//
// Created by movleaxedx on 13.10.19.
//


#pragma once
#include <memory>
#include <string>

#include <geometry.hpp>
#include <material.hpp>

namespace engine
{
    class mesh
    {
    public:
        mesh() = default;
        ~mesh() = default;

        explicit mesh(std::string, std::shared_ptr<geometry>, std::shared_ptr<material> material = nullptr);
        std::shared_ptr<geometry> get_geometry();
        void set_geometry(std::shared_ptr<geometry>);
        void attach_material(std::shared_ptr<material>);
        std::string get_name() const;

        void draw();

    private:
        std::shared_ptr<geometry> m_geometry;
        std::shared_ptr<material> m_material;
        std::string m_name;
    };
} // namespace engine
