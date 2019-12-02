//
// Created by movleaxedx on 15.10.19.
//
#include <assets/image_importer.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


std::shared_ptr<engine::interfaces::texture> engine::image_importer::import() const
{
    int32_t channels_count;
    int32_t width;
    int32_t height;

    auto data = stbi_load(m_parameters.path.c_str(), &width, &height, &channels_count, 0);

    return std::make_shared<engine::image_2d_texture>(
        m_parameters.name,
        engine::image{
            data,
            width,
            height,
            static_cast<image_format>(channels_count),
            stbi_image_free});
}


std::string engine::image_importer::get_name() const
{
    return m_parameters.name;
}


engine::image_importer::image_importer(const import_parameters& parameters)
    : m_parameters(parameters)
{
}
