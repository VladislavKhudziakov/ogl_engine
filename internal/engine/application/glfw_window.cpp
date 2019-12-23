//
// Created by movleaxedx on 23.12.19.
//

#include <glfw_window.hpp>
#include <ogl_application.hpp>

engine::glfw_window::glfw_window(const std::string& name, uint32_t w, uint32_t h)
    : base_window(name, w, h)
    , m_window(
          glfwCreateWindow(
              w,
              h,
              name.data(),
              nullptr,
              nullptr),
          [](GLFWwindow* window) {
              glfwDestroyWindow(window);
              glfwTerminate();
          })
{
    if (m_window == nullptr) {
        throw std::logic_error("Failed to create window");
    }

    glfwMakeContextCurrent(m_window.get());

    glfwSetFramebufferSizeCallback(m_window.get(), [](GLFWwindow* window, int width, int height) {
        auto engine = reinterpret_cast<ogl_application*>(glfwGetWindowUserPointer(window));
        const auto& curr_window = static_cast<glfw_window&>(engine->get_window());
        curr_window.on_window_size_changed(width, height);
    });
}
