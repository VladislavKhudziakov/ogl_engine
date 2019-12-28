//
// Created by movleaxedx on 28.10.19.
//

#include <mesh_instance.hpp>
#include <interfaces/component_visitor.hpp>


engine::mesh_instance::mesh_instance(std::shared_ptr<mesh_bucket> mesh)
    : m_mesh(std::move(mesh))
{
}


std::shared_ptr<engine::mesh_bucket> engine::mesh_instance::get_mesh() const
{
    return m_mesh;
}


void engine::mesh_instance::set_mesh(std::shared_ptr<mesh_bucket> mesh)
{
    m_mesh = std::move(mesh);
}


void engine::mesh_instance::visit(engine::interfaces::component_visitor& visitor, std::shared_ptr<scene_object>& ptr)
{
    visitor.accept(*this, ptr);
}
