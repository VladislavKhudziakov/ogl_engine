//
// Created by movleaxedx on 23.11.19.
//


#pragma once

#include <memory>

namespace engine
{
    class material_component;
    class scene_object;
}

namespace engine::interfaces
{
    class material_component_visitor
    {
    public:
        virtual ~material_component_visitor() = default;
        virtual void accept(material_component&, std::shared_ptr<scene_object>&) = 0;
    };
}
