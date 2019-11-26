//
// Created by movleaxedx on 26.11.19.
//

#include <environment_texture.hpp>
#include "env_texture_importer.hpp"

engine::env_texture_importer::env_texture_importer(
    const std::string& name,
    const std::array<std::string, 6>& images_paths,
    const texture_parameters& parameters)
    : m_name(name)
    , m_image_paths(images_paths)
    , m_parameters(parameters)
{
}


std::shared_ptr<engine::interfaces::texture> engine::env_texture_importer::import() const
{
    return std::make_shared<environment_texture>(m_name, m_image_paths, m_parameters);
}


std::string engine::env_texture_importer::get_name() const
{
    return m_name;
}
