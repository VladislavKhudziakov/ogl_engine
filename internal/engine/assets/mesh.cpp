//
// Created by movleaxedx on 13.10.19.
//

#include <mesh.hpp>
#include <common/bind_context.hpp>

engine::mesh::mesh(std::string name, std::shared_ptr<interfaces::geometry_buffer> geometry, std::shared_ptr<material> material)
    : m_geometry(std::move(geometry))
    , m_name(std::move(name))
    , m_material(std::move(material))
{
}


std::shared_ptr<engine::interfaces::geometry_buffer> engine::mesh::get_geometry()
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


std::string engine::mesh::get_name() const
{
    return m_name;
}


void engine::mesh::set_transformation(glm::mat4 transformation)
{
    m_transformation_matrix = transformation;
}


glm::mat4 engine::mesh::get_transformation() const
{
    return m_transformation_matrix;
}
