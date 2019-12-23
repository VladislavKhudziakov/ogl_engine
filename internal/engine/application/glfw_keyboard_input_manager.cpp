//
// Created by movleaxedx on 5.12.19.
//

#include <glfw_keyboard_input_manager.hpp>
#include <application/ogl_engine.hpp>
#include <key_event.hpp>

engine::glfw_keyboard_input_manager::glfw_keyboard_input_manager(GLFWwindow* window)
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mode) {
        auto* app = reinterpret_cast<ogl_engine*>(glfwGetWindowUserPointer(window));
        auto& curr_manager = static_cast<glfw_keyboard_input_manager&>(app->get_keyboard_manager());
        KEYBOARD_EVENT curr_event;
        KEY_CODE key_code{ KEY_CODE(key) };

        switch (action) {
        case GLFW_PRESS:
            curr_event = KEYBOARD_EVENT::PRESS;
            break;
        case GLFW_RELEASE:
            curr_event = KEYBOARD_EVENT::RELEASE;
            break;
        case GLFW_REPEAT:
            curr_event = KEYBOARD_EVENT::HOLD;
            break;
        default:
            throw std::runtime_error("ERROR: INVALID EVENT");
            break;
        }

        curr_manager.m_key_event_signal({curr_event, key_code});
    });
}
