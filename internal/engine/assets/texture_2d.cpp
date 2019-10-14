//
// Created by movleaxedx on 14.10.19.
//

#include <glad/glad.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include <stb_image.h>

#include <stdexcept>

#include <texture_2d.hpp>


engine::texture_2d::~texture_2d()
{
    glDeleteTextures(1, &m_texture_name);
}


void engine::texture_2d::bind(int slot)
{
    if (m_curr_slot >= 0) {
        throw std::logic_error("ERROR: TEXTURES WASN'T UNBOUNDED FROM CONTEXT");
    }

    m_curr_slot = GL_TEXTURE0 + slot;

    if (m_curr_slot >= GL_MAX_TEXTURE_UNITS) {
        throw std::logic_error("ERROR: TEXTURES LIMIT EXCEEDED");
    }

    glActiveTexture(m_curr_slot);
    glBindTexture(GL_TEXTURE_2D, m_texture_name);
}


void engine::texture_2d::unbind()
{
    if (m_curr_slot < 0) {
        throw std::logic_error("ERROR: TEXTURE ALREADY UNBOUNDED");
    }

    glActiveTexture(m_curr_slot);
    glBindTexture(GL_TEXTURE_2D, 0);

    m_curr_slot = -1;
}


engine::texture_2d_builder::texture_2d_builder()
    : m_texture(new texture_2d)
{
    glGenTextures(1, &m_texture->m_texture_name);
    glBindTexture(GL_TEXTURE_2D, m_texture->m_texture_name);
}


engine::texture_2d_builder& engine::texture_2d_builder::from_file(const std::string& file_name)
{
    int32_t width, height, channels_count;
    unsigned char* data = stbi_load(file_name.c_str(), &width, &height, &channels_count, 0);

    if (data == nullptr) {
        throw std::logic_error("ERROR: CANNOT LOAD IMAGE");
    }

    auto image_type = GL_RGBA;

    if (channels_count == 3) {
        image_type = GL_RGB;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, image_type, width, height, 0, image_type, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return *this;
}


std::shared_ptr<engine::texture_2d> engine::texture_2d_builder::generate_texture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    return m_texture;
}


std::shared_ptr<engine::texture_2d> engine::texture_2d_builder::generate_default_from_file(const std::string& file_name)
{
    using filtration_type = set_filtration::filtration_type;

    from_file(file_name);
    apply_command(generate_mipmap());
    apply_command(set_filtration { filtration_type::nearest });
    return generate_texture();
}


engine::texture_2d_builder& engine::texture_2d_builder::apply_command(const build_command_base& command)
{
    command.execute();
    return *this;
}


void engine::generate_mipmap::execute() const
{
    glGenerateMipmap(GL_TEXTURE_2D);
}


engine::set_filtration::set_filtration(engine::set_filtration::filtration_type type)
    : type(type)
{
}


void engine::set_filtration::execute() const
{
    uint32_t filer_type = 0;

    switch (type) {
    case filtration_type::linear:
        filer_type = GL_LINEAR;
        break;
    case filtration_type::nearest:
        filer_type = GL_NEAREST;
        break;
    default:
        throw std::logic_error("ERROR: INVALID FILTRATION TYPE");
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filer_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filer_type);
}