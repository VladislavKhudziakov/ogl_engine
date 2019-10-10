//
// Created by movleaxedx on 10.10.19.
//

#pragma once

#include <memory>
#include <GLFW/glfw3.h>

//TODO: add input events system
namespace engine
{
  class scene;

  class application
  {

  public:
    void init_window(int32_t width, int32_t height, const std::string& name);
    static application& get();
    void exec();
    void process_input();
    void set_scene(std::unique_ptr<scene>);

  private:
    application();
    GLFWwindow* p_window;
    std::unique_ptr<GLFWwindow*> m_window;
    std::unique_ptr<scene> m_scene;
  };
}
