//
// Created by movleaxedx on 13.10.19.
//

#include <algorithm>
#include <assets/mesh_bucket.hpp>
#include <assets/mesh.hpp>

const engine::assets::mesh_t& engine::mesh_bucket::get_mesh(const std::string& name) const
{
    auto pred = [&](auto& mesh) {
        return mesh->get_name() == name;
    };

    auto founded_mesh = std::find_if(m_meshes.begin(), m_meshes.end(), pred);

    if (founded_mesh != m_meshes.end()) {
        return *founded_mesh;
    }

    throw std::runtime_error("ERROR: CANNOT FIND MESH");
}


engine::assets::mesh_t& engine::mesh_bucket::get_mesh(const std::string& name)
{
    auto pred = [&](auto& mesh) {
      return mesh->get_name() == name;
    };

    auto founded_mesh = std::find_if(m_meshes.begin(), m_meshes.end(), pred);

    if (founded_mesh != m_meshes.end()) {
        return *founded_mesh;
    }

    throw std::runtime_error("ERROR: CANNOT FIND MESH");
}


void engine::mesh_bucket::append_mesh(assets::mesh_t mesh)
{
    m_meshes.emplace_back(std::move(mesh));
}


const std::vector<engine::assets::mesh_t>& engine::mesh_bucket::get_meshes() const
{
    return m_meshes;
}
