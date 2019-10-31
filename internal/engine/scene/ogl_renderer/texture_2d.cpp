
#include <glad/glad.h>
#include <scene/ogl_renderer/texture_2d.hpp>

engine::ogl::texture2d::texture2d(const std::string& file_path)
    : m_name(0)
{
    glGenTextures(1, &m_name);
    glBindTexture(GL_TEXTURE_2D, m_name);

    int32_t width, height, channels_count;
    unsigned char* data;
//    unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &channels_count, 0);

    if (data == nullptr) {
        throw std::logic_error("ERROR: CANNOT LOAD IMAGE");
    }

    if (channels_count < 3) {
        throw std::logic_error("ERROR: INVALID IMAGE FORMAT (SHOULD BE RGB/RGBA)");
    }

    auto image_type = GL_RGBA;

    if (channels_count == 3) {
        image_type = GL_RGB;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, image_type, width, height, 0, image_type, GL_UNSIGNED_BYTE, data);

//    stbi_image_free(data);
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
