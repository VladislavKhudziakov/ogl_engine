//
// Created by movleaxedx on 29.10.19.
//

#include <scene/ogl_renderer/scene_renderer.hpp>
#include <common/bind_context.hpp>
#include <common/for_each.hpp>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

engine::ogl::scene_renderer::scene_renderer(scene* scene)
    : m_scene(scene)
{
}


void engine::ogl::scene_renderer::draw_scene()
{
    assert(m_scene != nullptr);

    auto camera = m_scene->get_camera();
    auto projection = m_scene->get_perspective();

    auto fov = glm::radians(camera.get_fov());
    m_projection_matrix = glm::perspective(fov, 800.0f / 600.0f, projection.get_znear(), projection.get_zfar());
    m_view_matrix = glm::lookAt(camera.get_position(), camera.get_direction(), glm::vec3(0, 1, 0));
    m_world_matrix = m_projection_matrix * m_view_matrix;

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    process_nodes(m_scene->get_root());
}


void engine::ogl::scene_renderer::process_nodes(std::shared_ptr<scene_object> object)
{
    auto components = object->get_components();

    for_each(components, [&](auto&& component) {
        if (component != nullptr) {
            component->visit(*this, object);
        }
    });

    auto children = object->get_children();

    for (auto& child : children) {
        process_nodes(child);
    }
}


void engine::ogl::scene_renderer::accept(engine::material_component& component, std::shared_ptr<scene_object>& object)
{
    //todo material semantic
}


void engine::ogl::scene_renderer::accept(engine::mesh_instance& instance, std::shared_ptr<scene_object>& object)
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


void engine::ogl::scene_renderer::accept(engine::transformation& transformation, std::shared_ptr<scene_object>& object)
{
    if (auto parent = object->get_parent()) {
        auto parent_transform = parent->get_transformation_matrix();
        object->set_transformation_matrix(parent_transform * transformation.calculate());
    } else {
        object->set_transformation_matrix(transformation.calculate());
    }
}


void engine::ogl::scene_renderer::set_scene(scene* scene)
{
    m_scene = scene;
}
