//
// Created by movleaxedx on 28.10.19.
//

#include <mesh_instance.hpp>


engine::mesh_instance::mesh_instance(std::shared_ptr<mesh_data> mesh)
    : m_mesh(std::move(mesh))
{
}


std::shared_ptr<engine::mesh_data> engine::mesh_instance::get_mesh() const
{
    return m_mesh;
}


void engine::mesh_instance::set_mesh(std::shared_ptr<mesh_data> mesh)
{
    m_mesh = std::move(mesh);
}
