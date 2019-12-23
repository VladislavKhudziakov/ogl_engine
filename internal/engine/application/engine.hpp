//
// Created by movleaxedx on 23.12.19.
//


#pragma once


#include <application/keyboard_input_manager.hpp>
#include <application/mouse_input_manager.hpp>
#include <application/base_window.hpp>
#include <assets/assets_manager.hpp>
#include <scene/scene.hpp>

#include <memory>


namespace engine
{
    class engine_impl;

    class rendering_engine
    {
    public:
        rendering_engine();
        ~rendering_engine();

        void init_window(int32_t, int32_t, std::string);
        void exec();
        const keyboard_input_manager& get_keyboard_manager() const;
        const mouse_input_manager& get_mouse_manager() const;
        keyboard_input_manager& get_keyboard_manager();
        mouse_input_manager& get_mouse_manager();
        const scene& get_scene() const;
        scene& get_scene();
        assets_manager& get_assets_manager();
        const assets_manager& get_assets_manager() const;
        const base_window& get_window() const;
        base_window& get_window();

    private:
        std::unique_ptr<engine_impl> p_impl;
    };
}

