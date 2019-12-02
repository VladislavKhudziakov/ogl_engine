//
// Created by movleaxedx on 26.11.19.
//

#include <environment_texture.hpp>
#include <assets/env_texture_importer.hpp>
#include <stb/stb_image.h>

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
    int32_t last_channels_count = -1;
    int32_t last_width = -1;
    int32_t last_height = -1;

    std::vector<image> images{};
    images.reserve(6);

    for (const auto& path : m_image_paths) {
        int32_t channels_count;
        int32_t width;
        int32_t height;

        auto data = stbi_load(path.c_str(), &width, &height, &channels_count,0);

        if (channels_count < 3 || channels_count > 4) {
            throw std::runtime_error("ERROR: invalid image_2d_texture format");
        }

        if (last_channels_count > 0 && channels_count != last_channels_count) {
            throw std::runtime_error("ERROR: different images format");
        }

        if (last_width > 0 && last_height > 0 && width != last_width && height != last_height) {
            throw std::runtime_error("ERROR: different images size");
        }

        images.emplace_back(data, width, height, static_cast<image_format>(channels_count), stbi_image_free);
    }

    return std::make_shared<environment_texture>(m_name, std::move(images), m_parameters);
}


std::string engine::env_texture_importer::get_name() const
{
    return m_name;
}
