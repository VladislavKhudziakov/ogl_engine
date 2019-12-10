//
// Created by movleaxedx on 5.12.19.
//

#include <iostream>
#include "glfw_keyboard_input_manager.hpp"


using namespace engine;

glfw_keyboard_input_manager::glfw_keyboard_input_manager(
    //    const std::shared_ptr<GLFWwindow>& window)
    GLFWwindow* window)
    : p_window(window)
{
    set_window(p_window);
}

void glfw_keyboard_input_manager::on_key_event(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << "Called\n";
}

void glfw_keyboard_input_manager::set_window(GLFWwindow* window)
{
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    using std::placeholders::_4;
    using std::placeholders::_5;

    p_window = window;

    m_cb = std::bind(&glfw_keyboard_input_manager::on_key_event, this, _1, _2, _3, _4, _5);
    // glfwSetKeyCallback(p_window, m_cb.target());
}
