//
// Created by movleaxedx on 23.12.19.
//


#pragma once

#include <boost/signals2/signal.hpp>
#include <cstdint>
#include <string>

namespace engine
{
    class base_window
    {
    public:
        base_window(const std::string&, uint32_t, uint32_t);
        virtual ~base_window() = default;
        const std::string& get_name() const;
        std::pair<uint32_t, uint32_t> get_size() const;
        void subscribe_window_resize_handler(const std::function<void(uint32_t, uint32_t)>&);

    protected:
        uint32_t m_width;
        uint32_t m_height;
        std::string m_name;
        boost::signals2::signal<void(uint32_t, uint32_t)> on_window_size_changed;
    };
}
