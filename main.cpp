#include <application.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fstream>
#include <iostream>
#include <scene.hpp>

// TODO: easy deploy
// TODO: forward declaration
// TODO: settings?

int main()
{
    auto& app = engine::application::get();
    app.init_window(800, 600, "test");

    Assimp::Importer importer;

    auto scene = importer.ReadFile("../internal/resources/cube.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return -1;
    }

    std::vector<engine::mesh::vertex> cube_vertices;
    std::vector<int> cube_indices;

    if (scene->mNumMeshes > 0) {
        auto first_mesh = scene->mMeshes[0];
        for (size_t i = 0; i < first_mesh->mNumVertices; ++i) {
            engine::mesh::vertex vertex{first_mesh->mVertices[i].x,
                                        first_mesh->mVertices[i].y,
                                        first_mesh->mVertices[i].z,
                                        first_mesh->mTextureCoords[0][i].x,
                                        first_mesh->mTextureCoords[0][i].y,
                                        first_mesh->mNormals[i].x,
                                        first_mesh->mNormals[i].y,
                                        first_mesh->mNormals[i].z};

            cube_vertices.emplace_back(vertex);
        }

        for (size_t i = 0; i < first_mesh->mNumFaces; ++i) {
            for (size_t j = 0; j < first_mesh->mFaces[i].mNumIndices; ++j) {
                cube_indices.emplace_back(first_mesh->mFaces[i].mIndices[j]);
            }
        }
    }

    std::string vShaderSource;
    std::string fShaderSource;

    std::ifstream fin;
    fin.open("../internal/engine/shaders/test.vert");
    std::getline(fin, vShaderSource, '\0');
    fin.close();

    fin.open("../internal/engine/shaders/test.frag");
    std::getline(fin, fShaderSource, '\0');
    fin.close();

    engine::shader_program pog(vShaderSource, fShaderSource);

    auto mesh = engine::mesh_builder().generate_default_mesh(cube_vertices, cube_indices);

    auto mesh_scene = std::make_unique<engine::scene>();
    mesh_scene->set_object(std::make_unique<engine::scene_object>(std::move(mesh), pog));
    app.set_scene(std::move(mesh_scene));
    app.exec();

    return 0;
}
