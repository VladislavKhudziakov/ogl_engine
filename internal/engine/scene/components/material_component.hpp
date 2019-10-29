//
// Created by movleaxedx on 28.10.19.
//


#pragma once

#include <interfaces/component.hpp>
#include <material.hpp>


namespace engine
{
    class material_component : public interfaces::component
    {
    public:
        explicit material_component(std::shared_ptr<material>);
        ~material_component() override = default;

        std::shared_ptr<material> get_material() const;
        void set_material(std::shared_ptr<material>);
        void visit(interfaces::component_visitor& visitor, std::shared_ptr<scene_object>& ptr) override;

    private:
        std::shared_ptr<material> m_material;
    };
} // namespace engine
