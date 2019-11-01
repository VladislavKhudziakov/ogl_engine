//
// Created by movleaxedx on 29.10.19.
//

#include <scene/ogl_renderer/scene_renderer.hpp>
#include <common/for_each.hpp>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <assets/image.hpp>
#include "texture_2d.hpp"
#include "vertex_buffer.hpp"

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

        cache_material(material->get_material());
        bind_material(material->get_material());

        const auto& gpu_program = m_cache.get_resource<ogl::shader_program>(
            material->get_material()->get_shader()->get_name());

        gpu_program->apply_uniform_command(engine::ogl::set_mat4_uniform(
            "u_mvp", m_world_matrix * object->get_transformation_matrix()));

        for (const auto& mesh : mesh_data->get_meshes()) {
            cache_geometry(mesh->get_geometry());
            draw_geometry(mesh->get_geometry());
        }

        release_material(material->get_material());
    } else {
        for (const auto& mesh : mesh_data->get_meshes()) {
            cache_material(mesh->get_material());
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


void engine::ogl::scene_renderer::cache_material(const std::shared_ptr<material>& material)
{
    const auto& textures = material->get_textures();
    const auto& shaders = material->get_shader();

    for (auto&& [shader_name, texture] : textures) {
        if (!m_cache.cached(texture->get_name())) {
            //todo replace on visitors / get_type ?
            auto casted_texture = std::dynamic_pointer_cast<engine::image>(texture);
            if (casted_texture != nullptr) {
                m_cache.emplace(casted_texture->get_name(), ogl::texture2d::from_image(*casted_texture));
            }
        }
    }

    if (!m_cache.cached(shaders->get_name())) {
        m_cache.emplace(shaders->get_name(), ogl::shader_program::from_program(*shaders));
        shaders->clear();
    }
}


void engine::ogl::scene_renderer::cache_geometry(const std::shared_ptr<geometry>& geometry)
{
    if (!m_cache.cached(geometry->get_name())) {
        m_cache.emplace(geometry->get_name(), ogl::vertex_buffer::from_geometry(*geometry));
    }
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
    for (auto&& [shader_uniform, texture] : textures) {
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
