#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <mesh.hpp>

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

  auto vs = glCreateShader(GL_VERTEX_SHADER);
  auto s = vShaderSource.c_str();
  glShaderSource(vs, 1, &s, nullptr);
  glCompileShader(vs);

  int32_t compile_status;
  glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_status);

  if (compile_status == GL_FALSE) {
    int32_t log_length = 0;
    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &log_length);
    auto log_buffer = new char[log_length];
    glGetShaderInfoLog(vs, log_length, &log_length, log_buffer);
    std::cout << log_buffer << std::endl;
    delete[] log_buffer;
  }

  auto fs = glCreateShader(GL_FRAGMENT_SHADER);
  s = fShaderSource.c_str();
  glShaderSource(fs, 1, &s, nullptr);
  glCompileShader(fs);

  glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_status);

  if (compile_status == GL_FALSE) {
    int32_t log_length = 0;
    glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &log_length);
    auto log_buffer = new char[log_length];
    glGetShaderInfoLog(fs, log_length, &log_length, log_buffer);
    std::cout << log_buffer << std::endl;
    delete[] log_buffer;
  }

  auto program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  int32_t status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    int32_t log_length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    auto log_buffer = new char[log_length];
    glGetProgramInfoLog(program, log_length, &log_length, log_buffer);
    std::cout << log_buffer << std::endl;
    delete[] log_buffer;
  }

  glUseProgram(program);

  std::vector<engine::mesh::vertex> vertices {
      { 0.5f, 0.5f, 0.0f, 0.0, 0.0, 1.0f, 0.0f, 0.0f },
      { 0.5f, -0.5f, 0.0f, 0.0, 0.0, 0.0f, 1.0f, 0.0f },
      { -0.5f, 0.5f, 0.0f, 0.0, 0.0, 0.0f, 0.0f, 1.0f },
      { -0.5f, -0.5f, 0.0f, 0.0, 0.0, 0.0f, 0.0f, 0.0f }
  };

  std::vector<int> indices {
      0, 1, 2, 1, 2, 3
  };

  engine::mesh mesh(vertices, indices);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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