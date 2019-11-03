//
// Created by movleaxedx on 3.11.19.
//


#include <scene/ogl_renderer/interfaces/texture.hpp>
#include <scene/ogl_renderer/texture_2d.hpp>
#include <scene/ogl_renderer/texture_converter.hpp>


void engine::ogl::texture_converter::accept(const engine::image& image) const
{
    m_texture = texture2d::from_image(image);
}


std::shared_ptr<engine::ogl::interfaces::texture> engine::ogl::texture_converter::get_texture() const
{
    return m_texture;
}
