//
// Created by movleaxedx on 25.11.19.
//

#include <array>
#include <stdexcept>
#include <glad/glad.h>

#include <scene/ogl_renderer/gl_helpers.hpp>
#include <assets/environment_texture.hpp>
#include <scene/ogl_renderer/cubemap.hpp>


std::unique_ptr<engine::ogl::cubemap> engine::ogl::cubemap::from_env_texture(const engine::environment_texture& env_tex)
{
    auto [width, height] = env_tex.get_size();

    std::array<unsigned char*, 6> images_data{};

    for (size_t i = 0; i < images_data.size(); ++i) {
        images_data.at(i) = env_tex.get_face(static_cast<environment_texture::FACE>(i)).raw_data();
    }

    cubemap_data data{width, height, env_tex.get_format(), images_data};

    return std::make_unique<engine::ogl::cubemap>(data);
}

engine::ogl::cubemap::cubemap(const cubemap_data& data)
{
    GL_SAFE_CALL(glGenTextures, 1, &m_name)
    GL_SAFE_CALL(glBindTexture, GL_TEXTURE_CUBE_MAP, m_name)

    uint32_t curr_format = GL_RGB;

    if (data.format == image_format::rgba) {
        curr_format = GL_RGBA;
    }

    for (size_t i = 0; i < data.data.size(); ++i) {
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0,
            curr_format,
            data.width,
            data.height,
            0,
            curr_format,
            GL_UNSIGNED_BYTE,
            data.data.at(i));
    }


    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    assert(glGetError() == GL_NO_ERROR);
}


engine::ogl::cubemap::~cubemap()
{
    GL_SAFE_CALL(glDeleteTextures, 1, &m_name);
}


void engine::ogl::cubemap::bind(int slot)
{
    if (m_curr_slot >= 0) {
        throw std::logic_error("ERROR: TEXTURES WASN'T UNBOUNDED FROM CONTEXT");
    }

    m_curr_slot = GL_TEXTURE0 + slot;

    if (m_curr_slot >= GL_MAX_TEXTURE_UNITS) {
        throw std::logic_error("ERROR: TEXTURES LIMIT EXCEEDED");
    }
    GL_SAFE_CALL(glActiveTexture, m_curr_slot);
    GL_SAFE_CALL(glBindTexture, GL_TEXTURE_CUBE_MAP, m_name);
}


void engine::ogl::cubemap::unbind()
{
    if (m_curr_slot < 0) {
        throw std::logic_error("ERROR: TEXTURE ALREADY UNBOUNDED");
    }

    GL_SAFE_CALL(glActiveTexture, m_curr_slot);
    GL_SAFE_CALL(glBindTexture, GL_TEXTURE_CUBE_MAP, 0);

    m_curr_slot = -1;
}
