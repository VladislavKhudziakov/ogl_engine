
#include <glad/glad.h>
#include <scene/ogl_renderer/texture_2d.hpp>

engine::ogl::texture2d::texture2d(const image_data& img_data)
    : m_name(0)
{
    glGenTextures(1, &m_name);
    glBindTexture(GL_TEXTURE_2D, m_name);

    if (img_data.data == nullptr) {
        throw std::logic_error("ERROR: CANNOT LOAD IMAGE");
    }

    if (img_data.channels_count < 3 || img_data.channels_count > 4) {
        throw std::logic_error("ERROR: INVALID IMAGE FORMAT (SHOULD BE RGB/RGBA)");
    }

    auto image_type = GL_RGBA;

    if (img_data.channels_count == 3) {
        image_type = GL_RGB;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, image_type, img_data.width, img_data.height, 0, image_type, GL_UNSIGNED_BYTE, img_data.data);
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

    glActiveTexture(m_curr_slot);
    glBindTexture(GL_TEXTURE_2D, m_name);
}


void engine::ogl::texture2d::unbind()
{
    if (m_curr_slot < 0) {
        throw std::logic_error("ERROR: TEXTURE ALREADY UNBOUNDED");
    }

    glActiveTexture(m_curr_slot);
    glBindTexture(GL_TEXTURE_2D, 0);

    m_curr_slot = -1;
}


engine::ogl::mipmapped::mipmapped(std::shared_ptr<interfaces::texture> next)
    : m_wrappee(std::move(next))
{
    glGenerateMipmap(GL_TEXTURE_2D);
}


void engine::ogl::mipmapped::bind(int slot)
{
    m_wrappee->bind(slot);
}


void engine::ogl::mipmapped::unbind()
{
    m_wrappee->unbind();
}
