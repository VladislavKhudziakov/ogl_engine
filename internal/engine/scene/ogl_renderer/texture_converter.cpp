//
// Created by movleaxedx on 3.11.19.
//


#include <scene/ogl_renderer/interfaces/texture.hpp>
#include <scene/ogl_renderer/texture_2d.hpp>
#include <scene/ogl_renderer/texture_converter.hpp>
#include <scene/ogl_renderer/cubemap.hpp>


void engine::ogl::texture_converter::accept(const engine::image& image) const
{
    m_texture = texture2d::from_image(image);
}


std::unique_ptr<engine::ogl::interfaces::texture> engine::ogl::texture_converter::get_texture() const
{
    if (m_texture) {
        return std::move(m_texture);
    }

    throw std::runtime_error("ERROR: converted image does not exist");
}


void engine::ogl::texture_converter::accept(const engine::environment_texture& texture) const
{
    m_texture = cubemap::from_env_texture(texture);
}
