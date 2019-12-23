//
// Created by movleaxedx on 2.12.19.
//

#include <assets/image.hpp>

engine::image::image(
    uint8_t* data,
    int32_t w,
    int32_t h,
    engine::image_format format,
    const std::function<void(uint8_t*)>& deleter)
    : p_data(data, deleter)
    , m_width(w)
    , m_height(h)
    , m_format(format)
{
}


uint8_t* engine::image::raw_data() const
{
    return p_data.get();
}


bool engine::image::compare_size(const engine::image& other)
{
    return m_width == other.m_width && m_height == other.m_height;
}


bool engine::image::compare_format(const engine::image& other)
{
    return m_format == other.m_format;
}


std::pair<int32_t, int32_t> engine::image::get_size() const
{
    return std::make_pair(m_width, m_height);
}


engine::image_format engine::image::get_format() const
{
    return m_format;
}
