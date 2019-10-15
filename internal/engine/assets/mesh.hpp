//
// Created by movleaxedx on 13.10.19.
//


#pragma once
#include <memory>
#include <string>

#include <geometry.hpp>


namespace engine
{
    class mesh
    {
    public:
        mesh() = default;
        ~mesh() = default;

        explicit mesh(std::shared_ptr<geometry> geometry, std::string name);
        std::shared_ptr<geometry> get_geometry();
        std::string get_name() const;
        void set_geometry(std::shared_ptr<geometry>);
        void draw();
        //TODO get_material set_material
    private:
        std::shared_ptr<geometry> m_geometry;
        std::string m_name;
        //TODO: materal m_material
    };
}

