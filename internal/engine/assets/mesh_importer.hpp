//
// Created by movleaxedx on 13.10.19.
//


#pragma once

#include <interfaces/importer.hpp>
#include <interfaces/file_loader.hpp>
#include <mesh_instance.hpp>

class aiScene;
class aiMesh;

namespace engine
{
    class geometry_builder;

    class mesh_importer : public interfaces::importer<mesh_instance>
    {
    public:
        explicit mesh_importer(engine::interfaces::file_loader<std::string>&);
        ~mesh_importer() override = default;
        std::shared_ptr<mesh_instance> import(const std::string& file_name) const override;

    private:
        static void copy_vertices(std::vector<geometry::vertex>&, const aiMesh*);
        static void copy_indices(std::vector<int32_t>&, const aiMesh*);
        static void validate_file(const aiScene*);

        interfaces::file_loader<std::string>& m_loader;
    };
} // namespace engine
