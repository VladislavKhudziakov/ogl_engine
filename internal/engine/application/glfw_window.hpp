//
// Created by movleaxedx on 23.12.19.
//


#pragma once

#include <base_window.hpp>
#include <GLFW/glfw3.h>

namespace engine
{
    class glfw_window : public base_window
    {
        friend class ogl_engine;

    public:
        glfw_window(const std::string&, uint32_t, uint32_t);
    private:
        std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> m_window;
    };
}

