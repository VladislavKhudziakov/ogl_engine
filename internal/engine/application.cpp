//
// Created by movleaxedx on 10.10.19.
//

//ogl libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//std libs
#include <cassert>

#include <scene.hpp>
#include <application.hpp>


engine::application::application() : p_window(nullptr)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}



engine::application& engine::application::get()
{
  static application app;
  return app;
}



void engine::application::init_window(int32_t width, int32_t height, const std::string& name)
{
  p_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

  if (p_window == nullptr) {
    throw std::logic_error("Failed to create window");
  }

  glfwMakeContextCurrent(p_window);

  glfwSetFramebufferSizeCallback(p_window, [](GLFWwindow* window, int width, int height) {
    auto& app = engine::application::get();
    glViewport(0, 0, width, height);
    //TODO: framebuffer size changed signal, boost.signal2?
  });

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::logic_error("Failed to initialize GLAD");
  }
}



void engine::application::exec()
{
  assert(p_window != nullptr && "CANNOT EXECUTE APP WHILE WINDOW IS NOT INITIALIZED");

  while(!glfwWindowShouldClose(p_window)) {
    process_input();
    m_scene->draw();
    glfwSwapBuffers(p_window);
    glfwPollEvents();
  }

  glfwTerminate();
}



void engine::application::process_input()
{
  //TODO: add input events boost.signal2???
}



void engine::application::set_scene(std::unique_ptr<scene> scene)
{
  m_scene = std::move(scene);
}
