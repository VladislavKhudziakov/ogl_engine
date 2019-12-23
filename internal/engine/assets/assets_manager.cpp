
#include <assets/assets_manager.hpp>

engine::assets_manager::assets_manager()
{
    //todo add primitives
    //    mesh cube_mesh();
    //    add(std::make_shared<engine::mesh_data>() , "__default_cube__");
}

void engine::assets_manager::release_resource(const std::string& res_name)
{
    auto it = m_storage.find(res_name);

    if (it != m_storage.end()) {
        m_storage.erase(it);
        return;
    }

    throw std::runtime_error("ERROR: RESOURCE WAS NOT FOUND");
}
