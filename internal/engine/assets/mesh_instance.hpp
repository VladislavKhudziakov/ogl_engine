//
// Created by movleaxedx on 13.10.19.
//


#pragma once

#include <vector>
#include <string>
#include <mesh.hpp>


namespace engine
{
    class mesh_instance
    {
    public:
        void draw();
        void append_mesh(std::shared_ptr<mesh>);
        std::shared_ptr<mesh> get_mesh(const std::string&) const;
    private:
        std::vector<std::shared_ptr<mesh>> m_meshes;
    };
} // namespace engine
