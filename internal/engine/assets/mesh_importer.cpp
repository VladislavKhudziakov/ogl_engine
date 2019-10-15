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


std::shared_ptr<engine::mesh_instance> engine::mesh_importer::import(const file_loader<std::string>& loader, const std::string& file_name)
{
    loader.load(file_name);
    auto file = loader.get_file();

    Assimp::Importer importer;
    auto file_data = importer.ReadFile(file_name, aiProcess_Triangulate | aiProcess_FlipUVs);

    validate_file(file_data);

    auto instance = std::make_shared<mesh_instance>();

    for (size_t i = 0; i < file_data->mNumMeshes; ++i) {
        auto curr_mesh = file_data->mMeshes[i];
        geometry_builder builder;
        std::vector<geometry::vertex> vertices;
        std::vector<int32_t> indices;
        copy_vertices(vertices, curr_mesh);
        copy_indices(indices, curr_mesh);
        instance->append_mesh(std::make_shared<mesh>(
            curr_mesh->mName.C_Str(),
            builder.generate_default_mesh(vertices, indices)));
    }

    return instance;
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
        vertices_list.push_back({
            mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z,
            mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y,
            mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z
        });
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
