//
// Created by movleaxedx on 17.10.19.
//

#include <assets/interfaces/texture_visitor.hpp>
#include <assets/image.hpp>

#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

engine::image::image(const std::string& name, const std::string& path, const texture_parameters& parameters)
    : m_name(name)
    , m_width(0)
    , m_height(0)
    , m_format(image_format::rgb)
    , p_data(nullptr)
    , m_parameters(parameters)
{
    int32_t channels_count;
    p_data = stbi_load(path.c_str(), &m_width, &m_height, &channels_count, 0);

    if (p_data == nullptr) {
        throw std::runtime_error("ERROR: CANNOT IMPORT IMAGE");
    }

    if (channels_count < 3 || channels_count > 4) {
        throw std::runtime_error("ERROR: INVALID IMAGE FORMAT");
    }

    if (channels_count == 4) {
        m_format = image_format::rgba;
    }
}


engine::image::~image()
{
    stbi_image_free(p_data);
}


const std::string& engine::image::get_name() const
{
    return m_name;
}


std::pair<int32_t, int32_t> engine::image::get_size() const
{
    return std::make_pair(m_width, m_height);
}


engine::image_format engine::image::get_format() const
{
    return m_format;
}


const unsigned char* engine::image::get_data() const
{
    return p_data;
}


int32_t engine::image::get_levels() const
{
    return 1;
}



const engine::texture_parameters& engine::image::get_parameters() const
{
    return m_parameters;
}



void engine::image::set_parameters(const engine::texture_parameters& parameters)
{
    m_parameters = parameters;
}


void engine::image::visit(const engine::interfaces::texture_visitor& visitor) const
{
    visitor.accept(*this);
}
