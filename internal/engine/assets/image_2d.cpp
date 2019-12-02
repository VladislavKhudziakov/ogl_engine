//
// Created by movleaxedx on 2.12.19.
//

#include <assets/image_2d.hpp>

engine::image2D::image2D(
    uint8_t* data,
    uint64_t w,
    uint64_t h,
    engine::image_format format,
    const std::function<void(uint8_t*)>& deallocator)
    : p_data(data)
    , m_width(w)
    , m_height(h)
    , m_format(format)
    , m_deallocator(deallocator)
{
}


engine::image2D::image2D(engine::image2D&& other) noexcept
{
    p_data = other.p_data;
    other.p_data = nullptr;
    m_width = other.m_width;
    m_height = other.m_height;
    m_format = other.m_format;
    m_deallocator = other.m_deallocator;
}


engine::image2D& engine::image2D::operator=(engine::image2D&& other) noexcept
{
    *this = std::move(other);
    return *this;
}


engine::image2D::~image2D()
{
    if (p_data) {
        m_deallocator(p_data);
    }
}


uint8_t* engine::image2D::raw_data() const
{
    return p_data;
}


bool engine::image2D::compare_size(const engine::image2D& other)
{
    return m_width == other.m_width && m_height == other.m_height;
}


bool engine::image2D::compare_format(const engine::image2D& other)
{
    return m_format == other.m_format;
}


std::pair<uint64_t, uint64_t> engine::image2D::get_size() const
{
    return std::make_pair(m_width, m_height);
}


engine::image_format engine::image2D::get_format() const
{
    return m_format;
}
