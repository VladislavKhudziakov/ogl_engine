#include <assets/image_2d_texture.hpp>
#include <scene/ogl_renderer/texture_2d.hpp>
#include <scene/ogl_renderer/gl_helpers.hpp>

#include <glad/glad.h>
#include <cassert>

engine::ogl::texture2d::texture2d(const image_data& img_data)
    : m_name(0)
{
    GL_SAFE_CALL(glGenTextures, 1, &m_name);
    GL_SAFE_CALL(glBindTexture, GL_TEXTURE_2D, m_name);

    if (img_data.data == nullptr) {
        throw std::logic_error("ERROR: CANNOT LOAD IMAGE");
    }

    auto image_type = GL_RGBA;

    if (img_data.format == image_format::rgb) {
        image_type = GL_RGB;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, image_type, img_data.width, img_data.height, 0, image_type, GL_UNSIGNED_BYTE, img_data.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    assert(glGetError() == GL_NO_ERROR);
}


std::unique_ptr<engine::ogl::texture2d> engine::ogl::texture2d::from_image(const engine::image_2d_texture& img)
{
    auto [width, height] = img.get_size();

    image_data data{width, height, img.get_format(), img.get_image().raw_data()};

    return std::make_unique<texture2d>(data);
}


engine::ogl::texture2d::~texture2d()
{
    glDeleteTextures(1, &m_name);
}


void engine::ogl::texture2d::bind(int slot)
{
    if (m_curr_slot >= 0) {
        throw std::logic_error("ERROR: TEXTURES WASN'T UNBOUNDED FROM CONTEXT");
    }

    m_curr_slot = GL_TEXTURE0 + slot;

    if (m_curr_slot >= GL_MAX_TEXTURE_UNITS) {
        throw std::logic_error("ERROR: TEXTURES LIMIT EXCEEDED");
    }

    GL_SAFE_CALL(glActiveTexture, m_curr_slot);
    GL_SAFE_CALL(glBindTexture, GL_TEXTURE_2D, m_name);
}


void engine::ogl::texture2d::unbind()
{
    if (m_curr_slot < 0) {
        throw std::logic_error("ERROR: TEXTURE ALREADY UNBOUNDED");
    }

    GL_SAFE_CALL(glActiveTexture, m_curr_slot);
    GL_SAFE_CALL(glBindTexture, GL_TEXTURE_2D, 0);

    m_curr_slot = -1;
}


engine::ogl::mipmapped::mipmapped(std::unique_ptr<interfaces::texture> next)
    : m_wrappee(std::move(next))
{
    GL_SAFE_CALL(glGenerateMipmap, GL_TEXTURE_2D);
}


void engine::ogl::mipmapped::bind(int slot)
{
    m_wrappee->bind(slot);
}


void engine::ogl::mipmapped::unbind()
{
    m_wrappee->unbind();
}
