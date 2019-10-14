//
// Created by movleaxedx on 14.10.19.
//


#pragma once

namespace engine::interfaces
{
    class texture
    {
    public:
        virtual ~texture() = default;
        virtual void bind(int) = 0;
        virtual void unbind() = 0;
    };
} // namespace engine::interfaces
