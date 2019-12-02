//
// Created by movleaxedx on 2.12.19.
//

#include <assets/image.hpp>

engine::image::image(
    uint8_t* data,
    int32_t w,
    int32_t h,
    engine::image_format format,
    const std::function<void(uint8_t*)>& deallocator)
    : p_data(data)
    , m_width(w)
    , m_height(h)
    , m_format(format)
    , m_deallocator(deallocator)
{
}


engine::image::image(engine::image&& other) noexcept
{
    p_data = other.p_data;
    other.p_data = nullptr;
    m_width = other.m_width;
    m_height = other.m_height;
    m_format = other.m_format;
    m_deallocator = other.m_deallocator;
}


engine::image& engine::image::operator=(engine::image&& other) noexcept
{
    *this = std::move(other);
    return *this;
}


engine::image::~image()
{
    if (p_data) {
        m_deallocator(p_data);
    }
}


uint8_t* engine::image::raw_data() const
{
    return p_data;
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
