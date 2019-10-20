//
// Created by movleaxedx on 10.10.19.
//

#pragma once

#include <memory>
#include <GLFW/glfw3.h>

#include <assets/assets_manager.hpp>

//TODO: add input events system
namespace engine
{
    class scene;

    class application
    {
    public:
        ~application() = default;

        void init_window(int32_t, int32_t, const std::string&);
        static application& get();
        void exec();
        void process_input();
        void set_scene(std::unique_ptr<scene>);
        std::shared_ptr<assets_manager> get_assets_manager();
    private:
        application();
        GLFWwindow* p_window;
        std::unique_ptr<scene> m_scene;
        std::shared_ptr<assets_manager> m_assets_manager;
    };
} // namespace engine
