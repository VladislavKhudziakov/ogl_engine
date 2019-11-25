//
// Created by movleaxedx on 31.10.19.
//

#include <assets/mesh.hpp>
#include <assets/mesh_data.hpp>
#include <assets/material.hpp>
#include <assets/geometry.hpp>
#include <assets/interfaces/texture.hpp>

#include <scene/ogl_renderer/gpu_cache.hpp>
#include <scene/ogl_renderer/vertex_buffer.hpp>

#include <texture_converter.hpp>


void engine::ogl::gpu_cache::acquire_geometry(const engine::geometry& geometry)
{
    if (auto it = m_res.find(geometry.get_name()); it != m_res.end()) {
        auto&& [name, res_ref] = *it;
        ++res_ref.refs_counter;
    } else {
        m_res.emplace(geometry.get_name(), ogl::vertex_buffer::from_geometry(geometry));
    }
}


void engine::ogl::gpu_cache::release_geometry(const engine::geometry& geometry)
{
    auto it = m_res.find(geometry.get_name());
    assert(it != m_res.end() && "ERROR: resource already released");

    auto&& [name, res_ref] = *it;
    if (--res_ref.refs_counter <= 0) {
        m_res.erase(it);
    }
}


void engine::ogl::gpu_cache::acquire_shader(const engine::shader_program& program)
{
    if (auto it = m_res.find(program.get_name()); it != m_res.end()) {
        auto&& [name, res_ref] = *it;
        ++res_ref.refs_counter;
    } else {
        m_res.emplace(program.get_name(), ogl::shader_program::from_program(program));
    }
}


void engine::ogl::gpu_cache::release_shader(const engine::shader_program& program)
{
    auto it = m_res.find(program.get_name());
    assert(it != m_res.end() && "ERROR: resource already released");

    auto&& [name, res_ref] = *it;
    if (--res_ref.refs_counter <= 0) {
        m_res.erase(it);
    }
}


void engine::ogl::gpu_cache::acquire_texture(const engine::interfaces::texture& texture)
{
    if (auto it = m_res.find(texture.get_name()); it != m_res.end()) {
        auto&& [name, res_ref] = *it;
        ++res_ref.refs_counter;
    } else {
        texture_converter converter;
        texture.visit(converter);
        m_res.emplace(texture.get_name(), converter.get_texture());
    }
}


void engine::ogl::gpu_cache::release_texture(const engine::interfaces::texture& texture)
{
    auto it = m_res.find(texture.get_name());
    assert(it != m_res.end() && "ERROR: resource already released");

    auto&& [name, res_ref] = *it;
    if (--res_ref.refs_counter <= 0) {
        m_res.erase(it);
    }
}


void engine::ogl::gpu_cache::acquire_material(const engine::material& material)
{
    const auto& textures = material.get_textures();
    acquire_shader(*material.get_shader());

    for (auto&& [shader_name, texture] : textures) {
        acquire_texture(*texture);
    }
}


void engine::ogl::gpu_cache::release_material(const engine::material& material)
{
    const auto& textures = material.get_textures();
    release_shader(*material.get_shader());

    for (auto&& [shader_name, texture] : textures) {
        release_texture(*texture);
    }
}


void engine::ogl::gpu_cache::acquire_mesh(const engine::mesh& mesh)
{
    acquire_geometry(*mesh.get_geometry());

    if (mesh.has_material()) {
        acquire_material(*mesh.get_material());
    }
}


void engine::ogl::gpu_cache::release_mesh(const engine::mesh& mesh)
{
    release_geometry(*mesh.get_geometry());

    if (mesh.has_material()) {
        release_material(*mesh.get_material());
    }
}


void engine::ogl::gpu_cache::acquire_mesh_data(const engine::mesh_data& mesh_data)
{
    const auto& meshes = mesh_data.get_meshes();

    for (auto& mesh : meshes) {
        acquire_mesh(*mesh);
    }
}


void engine::ogl::gpu_cache::release_mesh_data(const engine::mesh_data& mesh_data)
{
    const auto& meshes = mesh_data.get_meshes();

    for (auto& mesh : meshes) {
        release_mesh(*mesh);
    }
}
