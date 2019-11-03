//
// Created by movleaxedx on 13.10.19.
//

#include <mesh.hpp>


engine::mesh::mesh(std::string name, std::shared_ptr<geometry> geometry, std::shared_ptr<material> material)
    : m_geometry(std::move(geometry))
    , m_name(std::move(name))
    , m_material(std::move(material))
{
}


std::shared_ptr<engine::geometry> engine::mesh::get_geometry() const
{
    return m_geometry;
}


void engine::mesh::set_geometry(std::shared_ptr<geometry> geometry)
{
    m_geometry = std::move(geometry);
}


void engine::mesh::attach_material(std::shared_ptr<material> material)
{
    m_material = std::move(material);
}


const std::string& engine::mesh::get_name() const
{
    return m_name;
}


std::shared_ptr<engine::material> engine::mesh::get_material() const
{
    return m_material;
}


bool engine::mesh::has_material() const
{
    return m_material != nullptr;
}
