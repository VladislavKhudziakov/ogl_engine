//
// Created by movleaxedx on 29.10.19.
//


#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <scene/ogl_renderer/scene_renderer.hpp>
#include <scene/ogl_renderer/material_config_resolver.hpp>

#include <common/for_each.hpp>


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

    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glClearColor(0.0f, 177.0f / 255.0f, 64.0f / 255.0f, 1.0f);

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
    //todo remake
    auto material = component.get_material();

    material_config_resolver resolver(material->get_config());
    resolver.set_config();
}


void engine::ogl::scene_renderer::accept(engine::mesh_instance& instance, std::shared_ptr<scene_object>& object)
{
    auto mesh_data = instance.get_mesh();

    if (object->has_component<material_component>()) {
        auto c_material = object->get_component<material_component>();
        m_cache.cache_material(*c_material->get_material());
        bind_material(c_material->get_material());

        const auto& gpu_program = m_cache.get_resource<ogl::shader_program>(
            c_material->get_material()->get_shader()->get_name());

        gpu_program->apply_uniform_command(engine::ogl::set_mat4_uniform(
            "u_mvp", m_world_matrix * object->get_transformation_matrix()));

        gpu_program->apply_uniform_command(engine::ogl::set_mat4_uniform(
            "u_mv", m_world_matrix));

        gpu_program->apply_uniform_command(engine::ogl::set_mat4_uniform(
            "u_it_model", glm::inverse(glm::transpose(object->get_transformation_matrix()))));

        gpu_program->apply_uniform_command(engine::ogl::set_float_uniform_array(
            "u_light_sources", m_scene->get_light_sources()));

        for (const auto& mesh : mesh_data->get_meshes()) {
            const auto& geometry = mesh->get_geometry();
            m_cache.cache_geometry(*geometry);
            draw_geometry(geometry);
        }

        release_material(c_material->get_material());
    } else {
        m_cache.cache_mesh_data(*mesh_data);

        for (const auto& mesh : mesh_data->get_meshes()) {
            bind_material(mesh->get_material());

            const auto& gpu_program = m_cache.get_resource<ogl::shader_program>(
                mesh->get_material()->get_shader()->get_name());

            gpu_program->apply_uniform_command(engine::ogl::set_mat4_uniform(
                "u_mvp", m_world_matrix * object->get_transformation_matrix()));

            draw_geometry(mesh->get_geometry());

            release_material(mesh->get_material());
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


void engine::ogl::scene_renderer::draw_geometry(const std::shared_ptr<geometry>& geometry)
{
    const auto& buffer = m_cache.get_resource<ogl::interfaces::vertex_buffer>(geometry->get_name());
    buffer->bind();
    buffer->draw();
    buffer->unbind();
}


void engine::ogl::scene_renderer::bind_material(const std::shared_ptr<material>& material)
{
    const auto& gpu_program = m_cache.get_resource<ogl::shader_program>(material->get_shader()->get_name());
    gpu_program->bind();

    int curr_slot = 0;
    auto textures = material->get_textures();
    for (auto [shader_uniform, texture] : textures) {
        auto gpu_texture = m_cache.get_resource<ogl::interfaces::texture>(texture->get_name());
        gpu_texture->bind(curr_slot);
        gpu_program->apply_uniform_command(set_int_uniform(shader_uniform, curr_slot));
        curr_slot++;
    }
}


void engine::ogl::scene_renderer::release_material(const std::shared_ptr<material>& material)
{
    const auto& gpu_program = m_cache.get_resource<ogl::shader_program>(
        material->get_shader()->get_name());
    gpu_program->unbind();

    auto textures = material->get_textures();
    for (auto&& [shader_uniform, texture] : textures) {
        auto gpu_texture = m_cache.get_resource<ogl::interfaces::texture>(texture->get_name());
        gpu_texture->unbind();
    }
}
