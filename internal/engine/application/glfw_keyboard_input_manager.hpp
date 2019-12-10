//
// Created by movleaxedx on 5.12.19.
//


#pragma once

#include <application/keyboard_input_manager.hpp>

#include <memory>

#include <GLFW/glfw3.h>

namespace
{
    extern "C" void key_callback_helper(void* context, GLFWwindow* window, int key, int scancode, int action, int mode);
}

namespace engine
{
    class glfw_keyboard_input_manager : public keyboard_input_manager
    {
//        friend void ::key_callback_helper(void* context, GLFWwindow* window, int key, int scancode, int action, int mode);
    public:
        glfw_keyboard_input_manager() = default;
//        explicit glfw_keyboard_input_manager(const std::shared_ptr<GLFWwindow>&);
        explicit glfw_keyboard_input_manager(GLFWwindow*);
        void set_window(GLFWwindow*);
        ~glfw_keyboard_input_manager() override = default;
        void on_key_event(GLFWwindow* window, int key, int scancode, int action, int mode);
    private:
//        std::shared_ptr<GLFWwindow> m_window;
        GLFWwindow* p_window;
        std::function<void(GLFWwindow* window, int key, int scancode, int action, int mode)> m_cb;
    };
}

