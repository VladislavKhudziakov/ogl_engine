//
// Created by movleaxedx on 28.10.19.
//


#pragma once

#include <material.hpp>

namespace engine
{
    class material_component
    {
    public:
        explicit material_component(std::shared_ptr<material>);
        ~material_component() = default;

        std::shared_ptr<material> get_material() const;
        void set_material(std::shared_ptr<material>);

    private:
        std::shared_ptr<material> m_material;
    };
} // namespace engine
