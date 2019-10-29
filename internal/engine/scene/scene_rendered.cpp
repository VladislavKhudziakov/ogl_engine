//
// Created by movleaxedx on 29.10.19.
//

#include <scene_rendered.hpp>
#include <common/bind_context.hpp>
#include <common/for_each.hpp>

engine::scene_rendered::scene_rendered(std::shared_ptr<scene> scene)
    : m_scene(scene)
{
}


void engine::scene_rendered::draw_scene()
{
    auto scene_sptr = m_scene.lock();
    auto camera = scene_sptr->get_camera();
    auto projection = scene_sptr->get_perspective();


    auto fov = glm::radians(camera.get_fov());
    m_projection_matrix = glm::perspective(fov, 800.0f / 600.0f, projection.get_znear(), projection.get_zfar());
    m_view_matrix = glm::lookAt(camera.get_position(), camera.get_direction(), glm::vec3(0, 1, 0));
    m_world_matrix = m_projection_matrix * m_view_matrix;

    process_nodes(scene_sptr->get_root());
}


void engine::scene_rendered::process_nodes(std::shared_ptr<scene_object> object)
{
    auto components = object->get_components();

    for_each(components, [&](auto&& arg) {
        if (arg != nullptr) {
            arg->visit(*this, object);
        }
    });
}


void engine::scene_rendered::accept(engine::material_component& component, std::shared_ptr<scene_object>& object)
{
//    component.get_material()->bind();
//    component.get_material()->get_shader()->apply_uniform_command(
//        engine::set_mat4_uniform("u_mvp", m_world_matrix * object->get_transformation_matrix()));
}


void engine::scene_rendered::accept(engine::mesh_instance& instance, std::shared_ptr<scene_object>& object)
{
    auto mesh_data = instance.get_mesh();

    if (object->has_component<material_component>()) {
        auto material = object->get_component<material_component>();
        material->get_material()->bind();

        material->get_material()->get_shader()->apply_uniform_command(
        engine::set_mat4_uniform("u_mvp", m_world_matrix * object->get_transformation_matrix()));

        for (const auto& mesh : mesh_data->get_meshes()) {
            const auto& mesh_transformation = mesh->get_transformation();
            bind_context<engine::interfaces::geometry_buffer> context(*mesh->get_geometry());
            mesh->get_geometry()->draw();
        }

        material->get_material()->unbind();
    } else {
        for (const auto& mesh : mesh_data->get_meshes()) {
            const auto& mesh_transformation = mesh->get_transformation();

            auto material = mesh->get_material();
            material->bind();

            material->get_shader()->apply_uniform_command(
                engine::set_mat4_uniform("u_mvp", m_world_matrix * object->get_transformation_matrix()));
            bind_context<engine::interfaces::geometry_buffer> context(*mesh->get_geometry());

            mesh->get_geometry()->draw();

            material->unbind();
        }
    }
}


void engine::scene_rendered::accept(engine::transformation& transformation, std::shared_ptr<scene_object>& object)
{
    if (auto parent = object->get_parent()) {
        auto parent_transform = parent->get_transformation_matrix();
        object->set_transformation_matrix(parent_transform * transformation.calculate());
    } else {
        object->set_transformation_matrix(transformation.calculate());
    }
}
