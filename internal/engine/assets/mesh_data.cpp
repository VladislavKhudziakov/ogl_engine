//
// Created by movleaxedx on 13.10.19.
//

#include <algorithm>
#include <mesh_data.hpp>

std::shared_ptr<engine::mesh> engine::mesh_data::get_mesh(const std::string& name) const
{
    auto pred = [&](auto& mesh) {
        return mesh->get_name() == name;
    };

    auto founded_mesh = std::find_if(m_meshes.begin(), m_meshes.end(), pred);

    if (founded_mesh != m_meshes.end()) {
        return *founded_mesh;
    }

    return nullptr;
}


void engine::mesh_data::append_mesh(std::shared_ptr<mesh> mesh)
{
    m_meshes.emplace_back(std::move(mesh));
}


const std::vector<std::shared_ptr<engine::mesh>>& engine::mesh_data::get_meshes() const
{
    return m_meshes;
}
