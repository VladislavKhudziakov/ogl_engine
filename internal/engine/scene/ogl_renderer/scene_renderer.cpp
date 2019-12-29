//
// Created by movleaxedx on 29.10.19.
//


#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <scene/scene_object.hpp>
#include <scene/ogl_renderer/gl_helpers.hpp>
#include <scene/ogl_renderer/scene_renderer.hpp>
#include <scene/ogl_renderer/material_config_resolver.hpp>
#include <scene/ogl_renderer/shaders/shader_program.hpp>
#include <scene/ogl_renderer/shaders/shader_program_visitors.hpp>

#include <assets/mesh.hpp>
#include <assets/geometry.hpp>

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

    GL_SAFE_CALL(glClear, GL_COLOR_BUFFER_BIT);
    GL_SAFE_CALL(glClear, GL_DEPTH_BUFFER_BIT);
    GL_SAFE_CALL(glDepthFunc, GL_LEQUAL);
    GL_SAFE_CALL(glColorMask, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    GL_SAFE_CALL(glClearColor, 0.0f, 177.0f / 255.0f, 64.0f / 255.0f, 1.0f);

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

        assert(glGetError() == GL_NO_ERROR);

        gpu_program->visit(ogl::uniform_visitor([this, &object](int32_t location) {
            auto mvp_matrix = m_world_matrix * object->get_transformation_matrix();
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mvp_matrix));
        },"u_mvp"));

        gpu_program->visit(ogl::uniform_visitor([this](int32_t location) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_world_matrix));
        },"u_mv"));


        gpu_program->visit(ogl::uniform_visitor([&object](int32_t location) {
            auto transformation_matrix = object->get_transformation_matrix();
            transformation_matrix = glm::inverse(glm::transpose(transformation_matrix));
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(transformation_matrix));
        }, "u_it_model"));

        gpu_program->visit(ogl::uniform_visitor([this](int32_t location) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_view_matrix));
        }, "u_view"));


        gpu_program->visit(ogl::uniform_visitor([this](int32_t location) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_projection_matrix));
        }, "u_proj"));

        gpu_program->visit(ogl::uniform_visitor([this](int32_t location) {

            const auto& sources = m_scene->get_light_sources();
            std::vector<glm::vec3> light_positions;
            light_positions.reserve(sources.size());

            for (const auto& light_source : sources) {
              light_positions.emplace_back(light_source.get_position());
            }

            glUniform3fv(location, sources.size(), glm::value_ptr(light_positions.front()));
        }, "u_light_sources"));

        gpu_program->visit(ogl::uniform_visitor([this](int32_t location) {
            const auto& camera = m_scene->get_camera();
            glUniform3fv(location, 1, glm::value_ptr(camera.get_position()));
        }, "u_cam_pos"));

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


void engine::ogl::scene_renderer::draw_geometry(const assets::geometry_t& geometry)
{
    const auto& buffer = m_cache.get_resource<ogl::vertices_data>(geometry->get_name());
    glBindVertexArray(buffer->get_vertices_buffer());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->get_indices_buffer());
    glDrawElements(GL_TRIANGLES, geometry->get_vertices_count(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);;
}


void engine::ogl::scene_renderer::bind_material(const assets::material_t& material)
{
    const auto& gpu_program = m_cache.get_resource<ogl::shader_program>(material->get_shader()->get_name());
    auto name = material->get_shader()->get_name();
    glUseProgram(*gpu_program);

    int curr_slot = 0;
    auto textures = material->get_textures();
    for (auto [shader_uniform, texture] : textures) {
        const auto& gpu_texture = m_cache.get_resource<ogl::interfaces::texture>(texture->get_name());
        gpu_texture->bind(curr_slot);

        gpu_program->visit(ogl::uniform_visitor([curr_slot](int32_t location) {
            glUniform1i(location, curr_slot);
        }, shader_uniform));

        curr_slot++;
    }
}


void engine::ogl::scene_renderer::release_material(const assets::material_t& material)
{
    glUseProgram(0);

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
