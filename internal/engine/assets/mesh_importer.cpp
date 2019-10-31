//
// Created by movleaxedx on 13.10.19.
//

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <stdexcept>
#include <vector>

#include <geometry.hpp>
#include <mesh_importer.hpp>


engine::mesh_importer::mesh_importer(const std::string& file_path, const std::string& name)
    : m_path(file_path)
    , m_mesh_name(name)
{
}


std::shared_ptr<engine::mesh_data> engine::mesh_importer::import() const
{
    Assimp::Importer importer;
    auto file_data = importer.ReadFile(m_path, aiProcess_Triangulate | aiProcess_FlipUVs);

    validate_file(file_data);

    m_mesh_instance = std::make_shared<mesh_data>();

    process_node(file_data, file_data->mRootNode);

    return m_mesh_instance;
}


std::string engine::mesh_importer::get_name() const
{
    return m_mesh_name;
}


void engine::mesh_importer::validate_file(const aiScene* file_data)
{
    if (!file_data) {
        throw std::logic_error("CANNOT LOAD FILE");
    }

    if (file_data->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        throw std::logic_error("FILE IMPORTING INCOMPLETE");
    }

    if (!file_data->mRootNode) {
        throw std::logic_error("CANNOT FIND ROOT NODE");
    }
}


void engine::mesh_importer::copy_vertices(std::vector<geometry::vertex>& vertices_list, const aiMesh* mesh)
{
    auto vertices_count = mesh->mNumVertices;
    vertices_list.reserve(vertices_count);

    for (size_t i = 0; i < vertices_count; ++i) {
        vertices_list.emplace_back(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z, mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
    }
}


void engine::mesh_importer::copy_indices(std::vector<int32_t>& indices_list, const aiMesh* mesh)
{
    for (size_t i = 0; i < mesh->mNumFaces; ++i) {
        for (size_t j = 0; j < mesh->mFaces[i].mNumIndices; ++j) {
            indices_list.emplace_back(mesh->mFaces[i].mIndices[j]);
        }
    }
}


void engine::mesh_importer::process_node(const aiScene* scene, const aiNode* node) const
{
    const auto& node_transformation = node->mTransformation;

    glm::mat4 transformation{{node_transformation.a1, node_transformation.a2, node_transformation.a3, node_transformation.a4},
                             {node_transformation.b1, node_transformation.b2, node_transformation.b3, node_transformation.b4},
                             {node_transformation.c1, node_transformation.c2, node_transformation.c3, node_transformation.c4},
                             {node_transformation.d1, node_transformation.d2, node_transformation.d3, node_transformation.d4}};


    for (int i = 0; i < node->mNumMeshes; ++i) {
        auto curr_mesh = scene->mMeshes[node->mMeshes[i]];
        std::vector<geometry::vertex> vertices;
        std::vector<int32_t> indices;

        copy_vertices(vertices, curr_mesh);
        copy_indices(indices, curr_mesh);

        auto mesh_geometry = std::make_shared<geometry>(vertices, indices);
        auto mesh = std::make_shared<engine::mesh>(curr_mesh->mName.C_Str(), mesh_geometry);
        mesh->set_transformation(transformation);
        m_mesh_instance->append_mesh(mesh);
    }

    for (int i = 0; i < node->mNumChildren; ++i) {
        process_node(scene, node->mChildren[i]);
    }
}
