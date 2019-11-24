//
// Created by movleaxedx on 29.10.19.
//


#pragma once

#include <scene/components/interfaces/transformation_visitor.hpp>
#include <scene/components/interfaces/mesh_instance_visitor.hpp>

namespace engine::interfaces
{
    class component_visitor : public transformation_visitor, public mesh_instance_visitor
    {
    public:
        using transformation_visitor::accept;
        using mesh_instance_visitor::accept;
        ~component_visitor() override = default;
    };
}
