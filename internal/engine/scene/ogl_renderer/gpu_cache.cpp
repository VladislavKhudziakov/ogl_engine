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


bool engine::ogl::gpu_cache::cached(const std::string& name) const
{
    return m_resources.find(name) != m_resources.end();
}


void engine::ogl::gpu_cache::cache_material(const engine::material& material)
{
    const auto& textures = material.get_textures();
    cache_shader(*material.get_shader());

    for (auto&& [shader_name, texture] : textures) {
        cache_texture(*texture);
    }
}


void engine::ogl::gpu_cache::cache_texture(const engine::interfaces::texture& texture)
{
    if (!cached(texture.get_name())) {
        texture_converter converter;
        texture.visit(converter);
        emplace(texture.get_name(), converter.get_texture());
    }
}


void engine::ogl::gpu_cache::cache_geometry(const engine::geometry& geometry)
{
    if (!cached(geometry.get_name())) {
        emplace(geometry.get_name(), ogl::vertex_buffer::from_geometry(geometry));
    }
}


void engine::ogl::gpu_cache::cache_shader(const engine::shader_program& program)
{
    if (!cached(program.get_name())) {
        emplace(program.get_name(), ogl::shader_program::from_program(program));
        return;
    }
}


void engine::ogl::gpu_cache::cache_mesh(const engine::mesh& a_mesh)
{
    cache_geometry(*a_mesh.get_geometry());

    if (a_mesh.has_material()) {
        cache_material(*a_mesh.get_material());
    }
}


void engine::ogl::gpu_cache::cache_mesh_data(const engine::mesh_data& a_mesh_data)
{
    const auto& meshes = a_mesh_data.get_meshes();

    for (auto& mesh : meshes)
    {
        cache_mesh(*mesh);
    }
}
