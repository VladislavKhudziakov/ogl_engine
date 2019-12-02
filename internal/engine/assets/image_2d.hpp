//
// Created by movleaxedx on 2.12.19.
//


#pragma once

#include <functional>
#include <common/image_format.hpp>

namespace engine
{
    class image2D
    {
    public:
        image2D(uint8_t*, uint64_t, uint64_t, image_format, const std::function<void(uint8_t*)>&);
        ~image2D();
        image2D(const image2D&) = delete;
        image2D& operator=(const image2D&) = delete;
        image2D(image2D&&) noexcept;
        image2D& operator=(image2D&&) noexcept;

        uint8_t* raw_data() const;
        bool compare_size(const image2D&);
        bool compare_format(const image2D&);

        std::pair<uint64_t, uint64_t> get_size() const;
        image_format get_format() const;

    private:
        uint8_t* p_data;
        uint64_t m_width{};
        uint64_t m_height{};
        image_format m_format;
        std::function<void(uint8_t*)> m_deallocator;
    };
}

