//
// Created by movleaxedx on 3.11.19.
//


#pragma once

namespace engine
{
    class image;
}

namespace engine::interfaces
{
    class texture;

    class texture_visitor
    {
    public:
        virtual ~texture_visitor() = default;
        virtual void accept(const image&) const = 0;
    };
}

