//
// Created by movleaxedx on 3.11.19.
//


//#include <scene/ogl_renderer/texture_2d.hpp
#include <scene/ogl_renderer/textures/texture_object.hpp>
#include <scene/ogl_renderer/textures/texture_converter.hpp>
//#include <scene/ogl_renderer/cubemap.hpp>


void engine::ogl::texture_converter::accept(const engine::image_2d_texture& image) const
{
    m_texture = std::make_unique<texture_object>(image);
}


std::unique_ptr<engine::ogl::texture_object> engine::ogl::texture_converter::get_texture() const
{
    if (m_texture) {
        return std::move(m_texture);
    }

    throw std::runtime_error("ERROR: converted image_2d_texture does not exist");
}


void engine::ogl::texture_converter::accept(const engine::environment_texture& texture) const
{
    m_texture = std::make_unique<texture_object>(texture);
}
