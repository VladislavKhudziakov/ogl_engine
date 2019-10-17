//
// Created by Vladislav Khudiakov on 10/15/19.
//

#include <assets_manager.hpp>

void engine::assets_manager::import_mesh(const interfaces::importer<mesh_instance>& importer, const std::string& name)
{
    m_meshes.emplace(importer.get_name(), importer.import());
}


void engine::assets_manager::import_shader(const interfaces::importer<shader_program>& importer, const std::string& name)
{
    m_shaders.emplace(importer.get_name(), importer.import());
}


void engine::assets_manager::import_texture(const interfaces::importer<interfaces::texture>& importer, const std::string& name)
{
    m_textures.emplace(importer.get_name(), importer.import());
}


void engine::assets_manager::import_material(const interfaces::importer<material>& importer, const std::string& name)
{
    m_materials.emplace(importer.get_name(), importer.import());
}


std::shared_ptr<engine::mesh_instance> engine::assets_manager::get_mesh(const std::string& name)
{
    try {
        return m_meshes.at(name);
    } catch (...) {
        return nullptr;
    }
}


std::shared_ptr<engine::shader_program> engine::assets_manager::get_shader(const std::string& name)
{
    try {
        return m_shaders.at(name);
    } catch (...) {
        return nullptr;
    }
}


std::shared_ptr<engine::interfaces::texture> engine::assets_manager::get_texture(const std::string& name)
{
    try {
        return m_textures.at(name);
    } catch (...) {
        return nullptr;
    }
}


std::shared_ptr<engine::material> engine::assets_manager::get_material(const std::string& name)
{
    try {
        return m_materials.at(name);
    } catch (...) {
        return nullptr;
    }
}