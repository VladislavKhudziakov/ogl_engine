//
// Created by Vladislav Khudiakov on 10/15/19.
//

#pragma once

#include <map>
#include <memory>

#include <assets/interfaces/texture.hpp>
#include <assets/types.hpp>
#include <common/material_config.hpp>

namespace engine
{
    class material
    {
    public:
        using material_textures_t = std::map<std::string, assets::texture_t>;

        explicit material(assets::shader_program_t);
        material() = default;
        virtual ~material() = default;

        assets::texture_t get_texture(const std::string&) const;
        void set_texture(const std::string&, const assets::texture_t&);
        const assets::shader_program_t& get_shader() const;
        void set_shader(const assets::shader_program_t&);
        void set_rendering_config(const material_config&);
        const material_config& get_config() const;

        const material_textures_t& get_textures() const;

    private:
        std::string m_name;
        material_textures_t m_textures;
        assets::shader_program_t m_shader;
        material_config m_config;
    };
} // namespace engine
