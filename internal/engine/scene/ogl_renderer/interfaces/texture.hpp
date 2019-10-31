//
// Created by movleaxedx on 31.10.19.
//


#pragma once


namespace engine::ogl::interfaces
{
    class texture
    {
    public:
        virtual ~texture() = default;
        virtual void bind(int) = 0;
        virtual void unbind() = 0;
    };
}

