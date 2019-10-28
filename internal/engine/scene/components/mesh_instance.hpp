//
// Created by movleaxedx on 28.10.19.
//


#pragma once

#include <mesh_data.hpp>


namespace engine
{
    class mesh_instance
    {
    public:
        explicit mesh_instance(std::shared_ptr<mesh_data>);
        ~mesh_instance() = default;
        std::shared_ptr<mesh_data> get_mesh() const;
        void set_mesh(std::shared_ptr<mesh_data>);

    private:
        std::shared_ptr<mesh_data> m_mesh;
    };
} // namespace engine
