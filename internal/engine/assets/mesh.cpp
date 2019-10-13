//
// Created by movleaxedx on 13.10.19.
//

#include <mesh.hpp>
#include <bind_context.hpp>

engine::mesh::mesh(std::shared_ptr<geometry> geometry, std::string name)
    : m_geometry(std::move(geometry))
    , m_name(std::move(name))
{
}


std::shared_ptr<engine::geometry> engine::mesh::get_geometry()
{
    return m_geometry;
}


void engine::mesh::draw()
{
    bind_context<engine::geometry> bind(*m_geometry);
    m_geometry->draw();
}


void engine::mesh::set_geometry(std::shared_ptr<geometry> geometry)
{
    m_geometry = std::move(geometry);
}


std::string engine::mesh::get_name() const
{
    return m_name;
}