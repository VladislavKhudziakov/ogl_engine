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
        void import_texture(const interfaces::importer<interfaces::texture>&, const std::string&);
        void import_mesh(const interfaces::importer<mesh_instance>&, const std::string&);
        void import_shader(const interfaces::importer<shader_program>&, const std::string&);
        void import_material(const interfaces::importer<material>&, const std::string&);

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
