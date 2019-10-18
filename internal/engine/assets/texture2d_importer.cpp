//
// Created by movleaxedx on 15.10.19.
//

#include "texture2d_importer.hpp"


std::shared_ptr<engine::interfaces::texture> engine::texture2d_importer::import() const
{
    std::shared_ptr<interfaces::texture> texture = std::make_shared<engine::texture2d>(m_parameters.path);

    if (m_parameters.mipmapped) {
        texture = std::make_shared<engine::mipmapped>(texture);
    }

    return texture;
}


std::string engine::texture2d_importer::get_name() const
{
    return m_parameters.name;
}


engine::texture2d_importer::texture2d_importer(const import_parameters& parameters)
    : m_parameters(parameters)
{
}
