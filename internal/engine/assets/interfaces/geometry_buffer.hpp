//
// Created by movleaxedx on 18.10.19.
//


#pragma once


namespace engine::interfaces
{
    class geometry_buffer
    {
    public:
        virtual ~geometry_buffer() = default;
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void draw() const = 0;
    };
} // namespace engine::interfaces
