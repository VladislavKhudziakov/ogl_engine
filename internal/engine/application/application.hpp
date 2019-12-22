//
// Created by movleaxedx on 10.10.19.
//

#pragma once

#include <string>
#include <memory>
#include <GLFW/glfw3.h>
#include <assets/assets_manager.hpp>
#include <application/glfw_keyboard_input_manager.hpp>

//TODO: add input events system
namespace engine
{
    class scene;

    class application
    {
    public:
        ~application();
        void init_window(int32_t, int32_t, std::string);
        static application& get();
        void exec();
        void set_scene(std::unique_ptr<scene>);
        std::shared_ptr<assets_manager> get_assets_manager();
        const glfw_keyboard_input_manager& get_keyboard_manager();

    private:
        application();
        //m_scene should be destroyed before p_window
        std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> p_window;
        std::unique_ptr<scene> m_scene;
        std::shared_ptr<assets_manager> m_assets_manager;
        std::optional<glfw_keyboard_input_manager> m_keyboard_manager;
    };
} // namespace engine
