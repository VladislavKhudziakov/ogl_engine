//
// Created by movleaxedx on 5.12.19.
//


#pragma once

#include <application/keyboard_input_manager.hpp>

#include <memory>

#include <GLFW/glfw3.h>

namespace engine
{
    class glfw_keyboard_input_manager : public keyboard_input_manager
    {
    public:
        glfw_keyboard_input_manager() = default;
        explicit glfw_keyboard_input_manager(GLFWwindow*);
        ~glfw_keyboard_input_manager() override = default;
    private:
    };
}

