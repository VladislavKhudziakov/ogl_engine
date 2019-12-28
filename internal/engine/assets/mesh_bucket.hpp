//
// Created by movleaxedx on 13.10.19.
//


#pragma once

#include <vector>
#include <string>
#include <assets/mesh.hpp>
#include <assets/types.hpp>


namespace engine
{
    class mesh_bucket
    {
    public:
        mesh_bucket() = default;
        ~mesh_bucket() = default;

        const std::vector<assets::mesh_t>& get_meshes() const;
        void append_mesh(assets::mesh_t);
        const assets::mesh_t& get_mesh(const std::string&) const;
        assets::mesh_t& get_mesh(const std::string&);
    private:
        std::vector<assets::mesh_t> m_meshes;
    };
} // namespace engine
