//
// Created by movleaxedx on 15.10.19.
//

#include <assets/image_importer.hpp>


std::shared_ptr<engine::interfaces::texture> engine::image_importer::import() const
{
    return std::make_shared<engine::image>(m_parameters.name, m_parameters.path);
}


std::string engine::image_importer::get_name() const
{
    return m_parameters.name;
}


engine::image_importer::image_importer(const import_parameters& parameters)
    : m_parameters(parameters)
{
}
