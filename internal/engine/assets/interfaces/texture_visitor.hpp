//
// Created by movleaxedx on 3.11.19.
//


#pragma once

namespace engine
{
    class image;
    class environment_texture;
}

namespace engine::interfaces
{
    class texture;

    class texture_visitor
    {
    public:
        virtual ~texture_visitor() = default;
        virtual void accept(const image&) const = 0;
        virtual void accept(const environment_texture&) const = 0;
    };
}

