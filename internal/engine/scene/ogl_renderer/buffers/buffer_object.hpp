//
// Created by movleaxedx on 29.12.19.
//


#pragma once

#include <cinttypes>

namespace engine::ogl
{
    class buffer_object
    {
    public:
        buffer_object();
        ~buffer_object();

        buffer_object(const buffer_object&) = delete;
        buffer_object& operator=(const buffer_object&) = delete;

        buffer_object(buffer_object&&) noexcept;
        buffer_object& operator=(buffer_object&&) noexcept;
        operator uint32_t() const;

    private:
        uint32_t m_name;
    };
} // namespace engine::ogl
