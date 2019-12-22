//
// Created by movleaxedx on 5.12.19.
//

#include <iostream>
#include <glfw_keyboard_input_manager.hpp>
#include <application/application.hpp>
#include <key_event.hpp>

engine::glfw_keyboard_input_manager::glfw_keyboard_input_manager(GLFWwindow* window)
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mode) {
        auto* app = reinterpret_cast<application*>(glfwGetWindowUserPointer(window));
        auto& curr_manager = app->get_keyboard_manager();
        curr_manager.m_key_event_signal({KEYBOARD_EVENT::PRESS, KEY_CODE::A});
    });
}
