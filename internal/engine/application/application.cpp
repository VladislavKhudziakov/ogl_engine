//
// Created by movleaxedx on 10.10.19.
//


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <common/defines.hpp>
#include <iostream>
#include <cassert>
#include <string>

#include <scene/scene.hpp>
#include <application/application.hpp>


engine::application::application()
    : p_window(nullptr, [&](GLFWwindow* window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    })
    , m_assets_manager(std::make_shared<assets_manager>())
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


void engine::application::init_window(int32_t width, int32_t height, std::string name)
{
    p_window.reset(glfwCreateWindow(width, height, name.data(), nullptr, nullptr));

    if (p_window == nullptr) {
        throw std::logic_error("Failed to create window");
    }

    glfwMakeContextCurrent(p_window.get());
    glfwSetWindowUserPointer(p_window.get(), this);
    m_keyboard_manager.emplace(p_window.get());
    m_mouse_manager.emplace(p_window.get());

    glfwSetFramebufferSizeCallback(p_window.get(), [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        //TODO: framebuffer size changed signal, boost.signal2?
    });

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::logic_error("Failed to initialize GLAD");
    }
}


void engine::application::exec()
{
    assert(p_window != nullptr && "CANNOT EXECUTE APP WHILE WINDOW IS NOT INITIALIZED");

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

    while (!glfwWindowShouldClose(p_window.get())) {
        m_scene->draw();
        glfwSwapBuffers(p_window.get());
        glfwPollEvents();
    }
}


void engine::application::set_scene(std::unique_ptr<scene> scene)
{
    m_scene = std::move(scene);
}


std::shared_ptr<engine::assets_manager> engine::application::get_assets_manager()
{
    return m_assets_manager;
}


const engine::glfw_keyboard_input_manager& engine::application::get_keyboard_manager() const
{
    return *m_keyboard_manager;
}


const engine::glfw_mouse_input_manager& engine::application::get_mouse_manager() const
{
    return *m_mouse_manager;
}


engine::glfw_keyboard_input_manager& engine::application::get_keyboard_manager()
{
    return *m_keyboard_manager;
}


engine::glfw_mouse_input_manager& engine::application::get_mouse_manager()
{
    return *m_mouse_manager;
}
