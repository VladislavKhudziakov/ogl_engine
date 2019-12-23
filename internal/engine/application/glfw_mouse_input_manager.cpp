//
// Created by movleaxedx on 22.12.19.
//

#include <glfw_mouse_input_manager.hpp>
#include <application/ogl_application.hpp>

engine::glfw_mouse_input_manager::glfw_mouse_input_manager(GLFWwindow* window)
{
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y){
        auto* app = reinterpret_cast<engine::ogl_application*>(glfwGetWindowUserPointer(window));
        auto& mouse_manager = static_cast<glfw_mouse_input_manager&>(app->get_mouse_manager());

        mouse_manager.on_cursor_position_changed(x, y);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        auto* app = reinterpret_cast<engine::ogl_application*>(glfwGetWindowUserPointer(window));
        auto& mouse_manager = static_cast<glfw_mouse_input_manager&>(app->get_mouse_manager());

        MOUSE_EVENT curr_event;
        MOUSE_BUTTON curr_button {MOUSE_BUTTON(button)};

        switch (action) {
        case GLFW_PRESS:
            curr_event = MOUSE_EVENT::PRESS;
            break;
        case GLFW_RELEASE:
            curr_event = MOUSE_EVENT::RELEASE;
            break;
        default:
            throw std::runtime_error("ERROR: INVALID EVENT");
        }

        mouse_manager.on_button_pressed(curr_button, curr_event);
    });
}
