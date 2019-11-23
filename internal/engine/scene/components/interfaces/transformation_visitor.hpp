//
// Created by movleaxedx on 23.11.19.
//


#pragma once

#include <memory>

namespace engine
{
    class transformation;
    class scene_object;
}

namespace engine::interfaces
{
    class transformation_visitor
    {
    public:
        virtual ~transformation_visitor() = default;
        virtual void accept(transformation&, std::shared_ptr<scene_object>&) = 0;
    };
}

