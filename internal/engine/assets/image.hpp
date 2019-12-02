//
// Created by movleaxedx on 2.12.19.
//


#pragma once

#include <functional>
#include <common/image_format.hpp>

namespace engine
{
    class image
    {
    public:
        image(uint8_t*, int32_t, int32_t, image_format, const std::function<void(uint8_t*)>&);
        ~image();
        image(const image&) = delete;
        image& operator=(const image&) = delete;
        image(image&&) noexcept;
        image& operator=(image&&) noexcept;

        uint8_t* raw_data() const;
        bool compare_size(const image&);
        bool compare_format(const image&);

        std::pair<int32_t, int32_t> get_size() const;
        image_format get_format() const;

    private:
        uint8_t* p_data;
        int32_t m_width{};
        int32_t m_height{};
        image_format m_format;
        std::function<void(uint8_t*)> m_deallocator;
    };
}

