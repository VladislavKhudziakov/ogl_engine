//
// Created by Vladislav Khudiakov on 10/15/19.
//

#pragma once

#include <map>
#include <memory>

#include <interfaces/texture.hpp>
#include <shader_program.hpp>

namespace engine
{
    //TODO: add material settings(blendind, culling ...)
    class material
    {
    public:
        explicit material(std::shared_ptr<engine::shader_program>);
        material() = default;
        virtual ~material() = default;

        std::shared_ptr<interfaces::texture> get_texture(const std::string&) const;
        void set_texture(const std::string&, std::shared_ptr<interfaces::texture>);
        std::shared_ptr<engine::shader_program> get_shader() const;
        void set_shader(std::shared_ptr<engine::shader_program>);
        void bind();
        void unbind();

    private:
        std::map<std::string, std::shared_ptr<interfaces::texture>> m_textures;
        std::shared_ptr<engine::shader_program> m_shader;
    };
} // namespace engine