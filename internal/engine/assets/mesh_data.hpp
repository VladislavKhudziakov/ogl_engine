//
// Created by movleaxedx on 13.10.19.
//


#pragma once

#include <vector>
#include <string>
#include <mesh.hpp>


namespace engine
{
    class mesh_data
    {
    public:
        mesh_data() = default;
        ~mesh_data() = default;

        const std::vector<std::shared_ptr<mesh>>& get_meshes() const;
        void append_mesh(std::shared_ptr<mesh>);
        std::shared_ptr<mesh> get_mesh(const std::string&) const;

    private:
        std::vector<std::shared_ptr<mesh>> m_meshes;
    };
} // namespace engine
