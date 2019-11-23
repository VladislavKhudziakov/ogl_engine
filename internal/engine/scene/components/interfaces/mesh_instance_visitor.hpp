//
// Created by movleaxedx on 23.11.19.
//


#pragma once

#include <memory>

namespace engine
{
    class mesh_instance;
    class scene_object;
}

namespace engine::interfaces
{
    class mesh_instance_visitor
    {
    public:
        virtual ~mesh_instance_visitor() = default;
        virtual void accept(mesh_instance&, std::shared_ptr<scene_object>&) = 0;
    };
}
