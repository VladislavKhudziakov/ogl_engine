//
// Created by Vladislav Khudiakov on 10/15/19.
//

#pragma once
#include <string>
#include <vector>
#include <map>

#include <mesh_importer.hpp>
#include <interfaces/texture.hpp>
#include <interfaces/importer.hpp>
#include <shader_program.hpp>
#include <texture.hpp>
#include <material.hpp>

namespace engine
{
    class assets_manager
    {
    public:
        engine::assets_manager& import_texture(const interfaces::importer<interfaces::texture>&);
        engine::assets_manager& import_mesh(const interfaces::importer<mesh_instance>&);
        engine::assets_manager& import_shader(const interfaces::importer<shader_program>&);
        engine::assets_manager& import_material(const interfaces::importer<material>&);

        std::shared_ptr<mesh_instance> get_mesh(const std::string&);
        std::shared_ptr<interfaces::texture> get_texture(const std::string&);
        std::shared_ptr<shader_program> get_shader(const std::string&);
        std::shared_ptr<material> get_material(const std::string&);

    private:
        std::map<std::string, std::shared_ptr<mesh_instance>> m_meshes;
        std::map<std::string, std::shared_ptr<interfaces::texture>> m_textures;
        std::map<std::string, std::shared_ptr<shader_program>> m_shaders;
        std::map<std::string, std::shared_ptr<material>> m_materials;
    };
} // namespace engine
