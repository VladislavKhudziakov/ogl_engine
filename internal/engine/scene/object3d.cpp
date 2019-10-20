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
    auto curr_transformation = mvp * get_component<transformation>().calculate();
    //TODO: FIX CONTEXT BINDING
    m_material->bind();
    m_material->get_shader()->apply_uniform_command(engine::set_mat4_uniform("u_mvp", curr_transformation));
    //TODO: m_material->apply_settings();
    m_mesh_instance->draw();
    m_material->unbind();
    scene_object::draw(mvp);
}
