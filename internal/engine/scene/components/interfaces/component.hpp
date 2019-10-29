//
// Created by movleaxedx on 29.10.19.
//


#pragma once

#include <memory>

namespace engine
{
    class scene_object;
}

namespace engine::interfaces
{
    class component_visitor;
}

namespace engine::interfaces
{
    class component
    {
    public:
        virtual ~component() = default;
        virtual void visit(component_visitor&, std::shared_ptr<scene_object>&) = 0;
    };
} // namespace engine::interfaces
