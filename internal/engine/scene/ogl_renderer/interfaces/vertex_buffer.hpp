//
// Created by movleaxedx on 31.10.19.
//


#pragma once

namespace engine::ogl::interfaces
{
    class vertex_buffer
    {
    public:
        virtual ~vertex_buffer() = default;
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void draw() = 0;
    };
} // namespace engine::ogl::interfaces
