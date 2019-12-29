//
// Created by movleaxedx on 29.12.19.
//

#include <glad/glad.h>

#include <algorithm>
#include <cassert>

#include <assets/environment_texture.hpp>
#include <assets/image_2d_texture.hpp>
#include <scene/ogl_renderer/textures/texture_object.hpp>


engine::ogl::texture_object::texture_object(uint32_t type)
    : m_name(0)
    , m_type(type)
{
    glGenTextures(1, &m_name);
    glBindTexture(m_type, m_name);

    if (glGetError() == GL_INVALID_ENUM) {
        glDeleteTextures(1, &m_name);
        throw std::logic_error("ERROR: INVALID TEXTURE TYPE");
    }

    glBindTexture(m_type, 0);
}


engine::ogl::texture_object::~texture_object()
{
    glDeleteTextures(1, &m_name);
}


engine::ogl::texture_object::texture_object(const engine::image_2d_texture& texture)
    : m_name(0)
    , m_type(GL_TEXTURE_2D)
{
    glGenTextures(1, &m_name);
    glBindTexture(GL_TEXTURE_2D, m_name);

    auto format = texture.get_format();
    auto [width, height] = texture.get_size();
    auto pixels = texture.get_image().raw_data();
    const auto& config = texture.get_parameters();

    assert(format == image_format::rgb || format == image_format::rgba);

    GLenum curr_format = GL_RGB;

    if (format == image_format::rgba) {
        curr_format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, curr_format, width, height, 0, curr_format, GL_UNSIGNED_BYTE, pixels);

    if (config.mips) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}


engine::ogl::texture_object::texture_object(const engine::environment_texture& texture)
    : m_name(0)
    , m_type(GL_TEXTURE_CUBE_MAP)
{
    glGenTextures(1, &m_name);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_name);


    auto format = texture.get_format();
    auto [width, height] = texture.get_size();
    std::array<unsigned char*, 6> images_pixels{};
    const auto& config = texture.get_parameters();

    for (size_t i = 0; i < images_pixels.size(); ++i) {
        images_pixels.at(i) = texture.get_face(static_cast<environment_texture::FACE>(i)).raw_data();
    }

    assert(format == image_format::rgb || format == image_format::rgba);

    GLenum curr_format = GL_RGB;

    if (format == image_format::rgba) {
        curr_format = GL_RGBA;
    }

    for (size_t i = 0; i < images_pixels.size(); ++i) {
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0,
            curr_format,
            width,
            height,
            0,
            curr_format,
            GL_UNSIGNED_BYTE,
            images_pixels.at(i));
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


engine::ogl::texture_object::texture_object(engine::ogl::texture_object&& src) noexcept
    : m_name(0)
{
    *this = std::move(src);
}


engine::ogl::texture_object& engine::ogl::texture_object::operator=(
    engine::ogl::texture_object&& src) noexcept
{
    m_name = src.m_name;
    src.m_name = 0;
    return *this;
}


engine::ogl::texture_object::operator uint32_t() const
{
    return m_name;
}


uint32_t engine::ogl::texture_object::get_type() const
{
    return m_type;
}
