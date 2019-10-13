//
// Created by movleaxedx on 13.10.19.
//


#pragma once

#include <file_loader.hpp>
#include <mesh_instance.hpp>

class aiScene;
class aiMesh;

namespace engine
{
    class geometry_builder;

    class mesh_importer
    {
    public:
        mesh_importer() = default;
        ~mesh_importer() = default;
        static std::shared_ptr<mesh_instance> import(const file_loader<std::string>&, const std::string& file_name);

    private:
        static void copy_vertices(std::vector<geometry::vertex>&, const aiMesh*);
        static void copy_indices(std::vector<int32_t>&, const aiMesh*);
        static void validate_file(const aiScene*);
    };
} // namespace engine
