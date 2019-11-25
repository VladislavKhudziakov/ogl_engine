//
// Created by movleaxedx on 25.11.19.
//

#include <stb_image.h>
#include <assets/interfaces/texture_visitor.hpp>
#include <assets/environment_texture.hpp>


engine::environment_texture::environment_texture(
    const std::string& name,
    const std::array<std::string, 6>& images_paths,
    const texture_parameters& parameters)
    : m_images()
    , m_name(name)
    , m_parameters(parameters)
{
    for (size_t i = 0; i < images_paths.size(); ++i) {
        set_face(images_paths.at(i), static_cast<FACE>(i));
    }
}


engine::environment_texture::~environment_texture()
{
    for (auto data : m_images) {
        stbi_image_free(data);
    }
}


const std::string& engine::environment_texture::get_name() const
{
    return m_name;
}


std::pair<int32_t, int32_t> engine::environment_texture::get_size() const
{
    return std::make_pair(m_width, m_height);
}


int32_t engine::environment_texture::get_levels() const
{
    return 1;
}


const engine::texture_parameters& engine::environment_texture::get_parameters() const
{
    return m_parameters;
}


void engine::environment_texture::set_parameters(const engine::texture_parameters& parameters)
{
    m_parameters = parameters;
}


void engine::environment_texture::visit(const engine::interfaces::texture_visitor& visitor) const
{
    visitor.accept(*this);
}


void engine::environment_texture::set_face(const std::string& path, engine::environment_texture::FACE face)
{
    if (m_images.at(static_cast<int64_t>(face)) != nullptr) {
        stbi_image_free(m_images.at(static_cast<int64_t>(face)));
    } else {
        int32_t channels_count;
        int32_t width;
        int32_t height;

        auto data = stbi_load(path.data(), &width, &height, &channels_count, 0);

        if ((m_width > 0 && width != m_width) || (m_height > 0 && height != m_height)) {
            throw std::runtime_error("ERROR: images size is different");
        }

        if (channels_count < 3) {
            throw std::runtime_error("ERROR: invalid image format");
        }

        if (m_format != image_format::undefined && channels_count != static_cast<int32_t>(m_format)) {
            throw std::runtime_error("ERROR: invalid image format");
        }

        m_images.at(static_cast<int64_t>(face)) = data;
    }
}


unsigned char* engine::environment_texture::get_face(engine::environment_texture::FACE face) const
{
    return m_images.at(static_cast<int64_t>(face));
}


engine::image_format engine::environment_texture::get_format() const
{
    return m_format;
}
