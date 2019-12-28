
#include <assets/assets_manager.hpp>
#include <assets/image.hpp>
#include <assets/image_2d_texture.hpp>
#include <assets/environment_texture.hpp>
#include <assets/mesh_bucket.hpp>
#include <assets/geometry.hpp>
#include <assets/mesh.hpp>
#include <assets/shader_program.hpp>
#include <assets/material.hpp>

engine::assets_manager::assets_manager()
{
    //todo add primitives
    //    mesh cube_mesh();
    //    add(std::make_shared<engine::mesh_bucket>() , "__default_cube__");
}


void engine::assets_manager::release_resource(const std::string& res_name)
{
    auto it = m_storage.find(res_name);

    if (it != m_storage.end()) {
        m_storage.erase(it);
        return;
    }

    throw std::runtime_error("ERROR: RESOURCE WAS NOT FOUND");
}


engine::assets::image_t engine::assets_manager::make_image(
    uint8_t* data,
    int32_t w,
    int32_t h,
    engine::image_format format,
    const std::function<void(uint8_t*)>& deleter)
{
    return std::make_shared<image>(data, w, h, format, deleter);
}


engine::assets::texture2d_t engine::assets_manager::make_texture2d(
    const std::string& name,
    engine::image img,
    const engine::texture_parameters& parameters)
{
    return std::make_shared<image_2d_texture>(name, std::move(img), parameters);
}


engine::assets::env_texture_t engine::assets_manager::make_env_texture(
    const std::string& name,
    std::vector<image> images,
    const engine::texture_parameters& parameters)
{
    return std::make_shared<environment_texture>(name, std::move(images), parameters);
}


engine::assets::mesh_bucket_t engine::assets_manager::make_mesh_bucket()
{
    return std::make_shared<mesh_bucket>();
}


engine::assets::geometry_t engine::assets_manager::make_geometry(
    const std::string& name,
    std::vector<vertex>&& vertices,
    std::vector<face>&& faces)
{
    return std::make_unique<geometry>(name, std::move(vertices), std::move(faces));
}


engine::assets::mesh_t engine::assets_manager::make_mesh()
{
    return std::make_unique<mesh>();
}


engine::assets::mesh_t engine::assets_manager::make_mesh(
    const std::string& name,
    engine::assets::geometry_t geometry,
    const engine::assets::material_t& material)
{
    return std::make_unique<mesh>(name, std::move(geometry), material);
}


engine::assets::geometry_t engine::assets_manager::make_geometry(
    const std::string& name,
    std::vector<vertex>& vertices,
    std::vector<face>& faces)
{
    return std::make_unique<geometry>(name, std::move(vertices), std::move(faces));
}
engine::assets::shader_program_t engine::assets_manager::make_shader_program(
    const std::string& name, std::vector<shader_program::shader>& shaders)
{
    return std::make_shared<shader_program>(name, std::move(shaders));
}
engine::assets::shader_program_t engine::assets_manager::make_shader_program(
    const std::string& name, std::vector<shader_program::shader>&& shaders)
{
    return std::make_shared<shader_program>(name, std::move(shaders));
}
