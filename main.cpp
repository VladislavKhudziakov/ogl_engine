#include <glad/glad.h>
#include <GLFW/glfw3.h>
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

  // glfw window creation
  // --------------------
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  Assimp::Importer importer;

  auto scene = importer.ReadFile("../internal/resources/cube.obj",
                                 aiProcess_Triangulate | aiProcess_FlipUVs);

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

    for (int i = 0; i < first_mesh->mNumFaces; ++i) {
      for (int j = 0; j < first_mesh->mFaces[i].mNumIndices; ++j) {
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

  engine::mesh mesh(cube_vertices, cube_indices);

  pog.bind();
  auto perspective = glm::perspective(glm::radians(60.0f), float(SCR_WIDTH) / float(SCR_HEIGHT), 1.0f, 100.0f);
  auto view = glm::lookAt(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  auto mvp = perspective * view;
  auto U_MVP = glGetUniformLocation(pog.get(), "u_mvp");
  glUniformMatrix4fv(U_MVP, 1, GL_FALSE, glm::value_ptr(mvp));

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    mesh.draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}