//
// Created by movleaxedx on 29.10.19.
//


#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <scene/scene_object.hpp>
#include <scene/ogl_renderer/scene_renderer.hpp>
#include <scene/ogl_renderer/material_config_resolver.hpp>

#include <common/for_each.hpp>

namespace engine::ogl
{
    class gpu_cache_resolver : public engine::interfaces::mesh_instance_visitor
    {
    public:
        explicit gpu_cache_resolver(engine::ogl::scene_renderer& renderer)
            : m_renderer(renderer)
        {
        }

        ~gpu_cache_resolver() override = default;

        void accept(engine::mesh_instance& instance, std::shared_ptr<engine::scene_object>& ptr) override
        {
            m_renderer.m_cache.acquire_mesh_data(*instance.get_mesh());
        }

    private:
        engine::ogl::scene_renderer& m_renderer;
    };
} // namespace engine::ogl


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
    glDepthFunc(GL_LEQUAL);
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


void engine::ogl::scene_renderer::accept(engine::mesh_instance& instance, std::shared_ptr<scene_object>& object)
{
    auto mesh_data = instance.get_mesh();

    for (const auto& mesh : mesh_data->get_meshes()) {
        bind_material(mesh->get_material());

        const auto& gpu_program = m_cache.get_resource<ogl::shader_program>(
            mesh->get_material()->get_shader()->get_name());

        gpu_program->apply_uniform_command(engine::ogl::set_mat4_uniform(
            "u_mvp", m_world_matrix * object->get_transformation_matrix()));

        gpu_program->apply_uniform_command(engine::ogl::set_mat4_uniform(
            "u_mv", m_world_matrix));

        gpu_program->apply_uniform_command(engine::ogl::set_mat4_uniform(
            "u_it_model", glm::inverse(glm::transpose(object->get_transformation_matrix()))));

        gpu_program->apply_uniform_command(engine::ogl::set_mat4_uniform(
            "u_view", m_view_matrix));

        gpu_program->apply_uniform_command(engine::ogl::set_mat4_uniform(
            "u_proj", m_projection_matrix));

        gpu_program->apply_uniform_command(engine::ogl::set_float_uniform_array(
            "u_light_sources", m_scene->get_light_sources()));

        gpu_program->apply_uniform_command(engine::ogl::set_vec3_uniform(
            "u_cam_pos", m_scene->get_camera().get_position()));

        material_config_resolver resolver(mesh->get_material()->get_config());
        resolver.set_config();

        draw_geometry(mesh->get_geometry());

        release_material(mesh->get_material());
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
    auto name = material->get_shader()->get_name();
    gpu_program->bind();

    int curr_slot = 0;
    auto textures = material->get_textures();
    for (auto [shader_uniform, texture] : textures) {
        const auto& gpu_texture = m_cache.get_resource<ogl::interfaces::texture>(texture->get_name());
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
        const auto& gpu_texture = m_cache.get_resource<ogl::interfaces::texture>(texture->get_name());
        gpu_texture->unbind();
    }
}


void engine::ogl::scene_renderer::acquire_gpu_resource(const std::shared_ptr<engine::interfaces::component>& component)
{
    //todo remove
    if (auto mesh_instance = std::dynamic_pointer_cast<engine::mesh_instance>(component); mesh_instance != nullptr) {
        m_cache.acquire_mesh_data(*mesh_instance->get_mesh());
    }
}


void engine::ogl::scene_renderer::release_gpu_resource(const std::shared_ptr<engine::interfaces::component>& component)
{
    //todo remove
    if (auto mesh_instance = std::dynamic_pointer_cast<engine::mesh_instance>(component); mesh_instance != nullptr) {
        m_cache.release_mesh_data(*mesh_instance->get_mesh());
    }
}
