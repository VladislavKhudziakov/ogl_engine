//
// Created by movleaxedx on 28.10.19.
//


#pragma once

#include <mesh_bucket.hpp>
#include <interfaces/component.hpp>


namespace engine
{
    class mesh_instance : public interfaces::component
    {
    public:
        explicit mesh_instance(std::shared_ptr<mesh_bucket>);
        ~mesh_instance() override = default;
        std::shared_ptr<mesh_bucket> get_mesh() const;
        void set_mesh(std::shared_ptr<mesh_bucket>);
        void visit(interfaces::component_visitor& visitor, std::shared_ptr<scene_object>& ptr) override;

    private:
        std::shared_ptr<mesh_bucket> m_mesh;
    };
} // namespace engine
