//
// Created by movleaxedx on 13.10.19.
//


#pragma once

#include <interfaces/importer.hpp>
#include <mesh_instance.hpp>

class aiScene;
class aiMesh;
class aiNode;

namespace engine
{
    class geometry_builder;

    class mesh_importer : public interfaces::importer<mesh_instance>
    {
    public:
        mesh_importer(const std::string&, const std::string&);
        ~mesh_importer() override = default;
        std::shared_ptr<mesh_instance> import() const override;
        std::string get_name() const override;

    private:
        void process_node(const aiScene*, const aiNode*) const;
        static void copy_vertices(std::vector<geometry::vertex>&, const aiMesh*);
        static void copy_indices(std::vector<int32_t>&, const aiMesh*);
        static void validate_file(const aiScene*);
        std::string m_path;
        std::string m_mesh_name;
        mutable std::shared_ptr<mesh_instance> m_mesh_instance;
    };
} // namespace engine
