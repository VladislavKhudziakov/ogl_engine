//
// Created by movleaxedx on 28.10.19.
//

#include <material_component.hpp>


engine::material_component::material_component(std::shared_ptr<material> material)
    : m_material(std::move(material))
{
}


std::shared_ptr<engine::material> engine::material_component::get_material() const
{
    return m_material;
}


void engine::material_component::set_material(std::shared_ptr<material> material)
{
    m_material = std::move(material);
}
