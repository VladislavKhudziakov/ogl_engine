//
// Created by movleaxedx on 29.12.19.
//


#pragma once
#include <cinttypes>

namespace engine::ogl
{
    class vertex_array_object
    {
    public:
        vertex_array_object();
        ~vertex_array_object();

        vertex_array_object(const vertex_array_object&) = delete;
        vertex_array_object& operator=(const vertex_array_object&) = delete;

        vertex_array_object(vertex_array_object&&) noexcept;
        vertex_array_object& operator=(vertex_array_object&&) noexcept;
        operator uint32_t() const;

    private:
        uint32_t m_name;
    };
} // namespace engine::ogl
