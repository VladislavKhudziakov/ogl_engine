#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <mesh.hpp>
#include <shader_program.hpp>
#include <application.hpp>
#include <scene.hpp>


int main()
{
  auto& app = engine::application::get();
  app.init_window(800, 600, "test");

  Assimp::Importer importer;

  auto scene = importer.ReadFile(
      "../internal/resources/cube.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
  {
    std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
    return -1;
  }

  std::vector<engine::mesh::vertex> cube_vertices;
  std::vector<int> cube_indices;

  if (scene->mNumMeshes > 0) {
    auto first_mesh = scene->mMeshes[0];
    for (size_t i = 0 ; i < first_mesh->mNumVertices; ++i) {
      engine::mesh::vertex vertex {
        first_mesh->mVertices[i].x, first_mesh->mVertices[i].y,first_mesh->mVertices[i].z,
        first_mesh->mTextureCoords[0][i].x, first_mesh->mTextureCoords[0][i].y,
        first_mesh->mNormals[i].x, first_mesh->mNormals[i].y, first_mesh->mNormals[i].z};

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

  pog.bind();
  auto perspective = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 1.0f, 100.0f);
  auto view = glm::lookAt(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  auto mvp = perspective * view;

  pog.apply_uniform_command(engine::set_mat4_uniform{"u_mvp", mvp});

  auto mesh_scene = std::make_unique<engine::scene>();
  mesh_scene->set_mesh(std::move(mesh));
  app.set_scene(std::move(mesh_scene));
  app.exec();

  return 0;
}
