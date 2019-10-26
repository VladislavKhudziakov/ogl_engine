//
// Created by movleaxedx on 20.10.19.
//

#include <object3d.hpp>
#include <common/bind_context.hpp>


engine::object3d::object3d(const std::string& name, std::shared_ptr<mesh_instance> mesh, std::shared_ptr<material> material)
    : scene_object(name)
    , m_mesh_instance(std::move(mesh))
    , m_material(std::move(material))
{
}


void engine::object3d::draw(glm::mat4 mvp) const
{
    //TODO: FIX CONTEXT BINDING
    m_material->bind();

    //TODO: m_material->apply_settings();

    auto node_transformation = mvp * get_component<transformation>().calculate();

    for (const auto& mesh : m_mesh_instance->get_meshes()) {
        const auto& mesh_transformation = mesh->get_transformation();
        m_material->get_shader()->apply_uniform_command(engine::set_mat4_uniform("u_mvp", node_transformation));
        bind_context<engine::interfaces::geometry_buffer> context(*mesh->get_geometry());
        mesh->get_geometry()->draw();
    }

    m_material->unbind();

    for (auto& child : m_children) {
        child->draw(node_transformation);
    }
}
