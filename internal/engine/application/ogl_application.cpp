//
// Created by movleaxedx on 10.10.19.
//


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <common/defines.hpp>
#include <iostream>
#include <cassert>
#include <string>

#include <glfw_window.hpp>
#include <scene/scene.hpp>
#include <scene/ogl_renderer/scene_renderer.hpp>
#include <application/ogl_application.hpp>
#include <application/glfw_keyboard_input_manager.hpp>
#include <application/glfw_mouse_input_manager.hpp>


engine::ogl_application::ogl_application()
    : engine_impl{std::make_unique<ogl::scene_renderer>()}
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}


void engine::ogl_application::init_window(int32_t width, int32_t height, std::string name)
{
    m_window = std::make_unique<glfw_window>(name, width, height);

    //TODO visitor?
    auto glfw_window_ptr = static_cast<glfw_window*>(m_window.get());

    glfwSetWindowUserPointer(glfw_window_ptr->m_window.get(), this);
    m_keyboard_manager = std::make_unique<glfw_keyboard_input_manager>(glfw_window_ptr->m_window.get());
    m_mouse_manager = std::make_unique<glfw_mouse_input_manager>(glfw_window_ptr->m_window.get());

    m_window->subscribe_window_resize_handler([](uint32_t w, uint32_t h) {
        glViewport(0, 0, w, h);
    });

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::logic_error("Failed to initialize GLAD");
    }
}


void engine::ogl_application::exec()
{
    if (!m_window) {
        throw std::runtime_error("ERROR: CANNOT EXECUTE APP WHILE WINDOW IS NOT INITIALIZED");
    }

#ifdef __ENGINE__GL_DEBUG__
    auto message_callback = [](GLenum source,
                               GLenum type,
                               GLuint id,
                               GLenum severity,
                               GLsizei length,
                               const GLchar* message,
                               const void* userParam) {
        std::stringstream ss{};
        ss << "OPENGL DEBUG ERROR: ";
        ss << message;

        throw std::runtime_error(ss.str());
    };


    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(message_callback, nullptr);
#endif // __ENGINE__GL_DEBUG__


    //TODO visitor?
    auto glfw_window_ptr = static_cast<glfw_window*>(m_window.get());

    while (!glfwWindowShouldClose(glfw_window_ptr->m_window.get())) {
        m_scene.draw();
        glfwSwapBuffers(glfw_window_ptr->m_window.get());
        glfwPollEvents();
    }
}