//
// Created by movleaxedx on 22.12.19.
//


#pragma once

#include <application/mouse_input_manager.hpp>
#include <GLFW/glfw3.h>

namespace engine
{
    class glfw_mouse_input_manager : public mouse_input_manager
    {
    public:
        explicit glfw_mouse_input_manager(GLFWwindow*);
        ~glfw_mouse_input_manager() override = default;
    };
}

