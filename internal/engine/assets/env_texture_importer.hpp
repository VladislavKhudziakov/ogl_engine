//
// Created by movleaxedx on 26.11.19.
//


#pragma once

#include <array>
#include <memory>

#include <assets/interfaces/importer.hpp>
#include <assets/interfaces/texture.hpp>

namespace engine
{
    class environment_texture;

    class env_texture_importer : public interfaces::importer<interfaces::texture>
    {
    public:
        env_texture_importer(const std::string&, const std::array<std::string, 6>&, const texture_parameters& = texture_parameters());
        ~env_texture_importer() override = default;
        std::shared_ptr<interfaces::texture> import() const override;
        std::string get_name() const override;

    private:
        std::string m_name;
        std::array<std::string, 6> m_image_paths;
        texture_parameters m_parameters;
    };
} // namespace engine
