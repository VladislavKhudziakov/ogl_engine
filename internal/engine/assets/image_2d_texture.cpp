//
// Created by movleaxedx on 17.10.19.
//

#include <assets/interfaces/texture_visitor.hpp>
#include <assets/image_2d_texture.hpp>

#include <stdexcept>

engine::image_2d_texture::image_2d_texture(const std::string& name, image img, const texture_parameters& parameters)
    : m_image(std::move(img))
    , m_name(name)
    , m_parameters(parameters)
{
}


const std::string& engine::image_2d_texture::get_name() const
{
    return m_name;
}


std::pair<int32_t, int32_t> engine::image_2d_texture::get_size() const
{
    return m_image.get_size();
}


engine::image_format engine::image_2d_texture::get_format() const
{
    return m_image.get_format();
}


const engine::image& engine::image_2d_texture::get_image() const
{
    return m_image;
}


int32_t engine::image_2d_texture::get_levels() const
{
    return 1;
}



const engine::texture_parameters& engine::image_2d_texture::get_parameters() const
{
    return m_parameters;
}



void engine::image_2d_texture::set_parameters(const engine::texture_parameters& parameters)
{
    m_parameters = parameters;
}


void engine::image_2d_texture::visit(const engine::interfaces::texture_visitor& visitor) const
{
    visitor.accept(*this);
}
