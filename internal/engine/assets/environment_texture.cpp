//
// Created by movleaxedx on 25.11.19.
//

#include <assets/interfaces/texture_visitor.hpp>
#include <assets/environment_texture.hpp>


engine::environment_texture::environment_texture(
    const std::string& name,
    std::vector<image2D> images,
    const texture_parameters& parameters)
    : m_images(std::move(images))
    , m_name(name)
    , m_parameters(parameters)
{
}


const std::string& engine::environment_texture::get_name() const
{
    return m_name;
}


std::pair<int32_t, int32_t> engine::environment_texture::get_size() const
{
    return m_images.at(0).get_size();
}


int32_t engine::environment_texture::get_levels() const
{
    return 1;
}


const engine::texture_parameters& engine::environment_texture::get_parameters() const
{
    return m_parameters;
}


void engine::environment_texture::set_parameters(const engine::texture_parameters& parameters)
{
    m_parameters = parameters;
}


void engine::environment_texture::visit(const engine::interfaces::texture_visitor& visitor) const
{
    visitor.accept(*this);
}


void engine::environment_texture::set_face(image2D image, engine::environment_texture::FACE face)
{
    m_images.at(static_cast<int64_t>(face)) = std::move(image);
}


const engine::image2D& engine::environment_texture::get_face(engine::environment_texture::FACE face) const
{
    return m_images.at(static_cast<int64_t>(face));
}


engine::image_format engine::environment_texture::get_format() const
{
    return m_images.at(0).get_format();
}
