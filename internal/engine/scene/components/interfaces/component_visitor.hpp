//
// Created by movleaxedx on 29.10.19.
//


#pragma once

#include <memory>

namespace engine
{
    class material_component;
    class mesh_instance;
    class transformation;

    class scene_object;
}

namespace engine::interfaces
{
    class component_visitor
    {
    public:
        virtual ~component_visitor() = default;
        virtual void accept(material_component&, std::shared_ptr<scene_object>&) = 0;
        virtual void accept(mesh_instance&, std::shared_ptr<scene_object>&) = 0;
        virtual void accept(transformation&, std::shared_ptr<scene_object>&) = 0;
    };
}
