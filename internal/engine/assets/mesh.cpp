//
// Created by movleaxedx on 13.10.19.
//

#include <mesh.hpp>
#include <geometry.hpp>
#include <material.hpp>


engine::mesh::mesh(const std::string& name, assets::geometry_t geometry, const assets::material_t& material)
    : m_geometry(std::move(geometry))
    , m_name(name)
    , m_material(material)
{
}


engine::mesh::~mesh() = default;


engine::assets::geometry_t& engine::mesh::get_geometry()
{
    return m_geometry;
}

const engine::assets::geometry_t& engine::mesh::get_geometry() const
{
    return m_geometry;
}


void engine::mesh::set_geometry(assets::geometry_t geometry)
{
    m_geometry = std::move(geometry);
}


void engine::mesh::attach_material(const assets::material_t& material)
{
    m_material = material;
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
