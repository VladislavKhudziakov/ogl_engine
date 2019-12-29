//
// Created by movleaxedx on 29.12.19.
//


#pragma once

#include <cinttypes>
#include <assets/types.hpp>

namespace engine::ogl
{
    class texture_object
    {
    public:
        explicit texture_object(const image_2d_texture&);
        explicit texture_object(const environment_texture&);
        texture_object(uint32_t type);
        ~texture_object();

        texture_object(const texture_object&) = delete;
        texture_object& operator=(const texture_object&) = delete;

        texture_object(texture_object&&) noexcept;
        texture_object& operator=(texture_object&&) noexcept;

        uint32_t get_type() const;

        operator uint32_t() const;

    private:
        uint32_t m_name;
        uint32_t m_type;

    };
} // namespace engine::ogl
