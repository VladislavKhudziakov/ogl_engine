//
// Created by movleaxedx on 23.12.19.
//

#include <application/base_window.hpp>

engine::base_window::base_window(const std::string& name, uint32_t w, uint32_t h)
    : m_width{w}
    , m_height{h}
    , m_name{name}
{
}


const std::string& engine::base_window::get_name() const
{
    return m_name;
}


std::pair<uint32_t, uint32_t> engine::base_window::get_size() const
{
    return std::make_pair(m_width, m_height);
}


void engine::base_window::subscribe_window_resize_handler(
    const std::function<void(uint32_t, uint32_t)>& handler)
{
    on_window_size_changed.connect(handler);
}
