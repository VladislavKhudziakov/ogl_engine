//
// Created by movleaxedx on 31.10.19.
//


#pragma once

#include <scene/ogl_renderer/interfaces/vertex_buffer.hpp>

namespace engine::ogl
{
    class vertex_buffer : public ogl::interfaces::vertex_buffer
    {
    public:
        vertex_buffer();
        ~vertex_buffer() override = default;
        void bind() override;
        void unbind() override;
    };
}

