//
// Created by movleaxedx on 23.12.19.
//


#pragma once

#include <assets/assets_manager.hpp>
#include <scene/interfaces/scene_renderer.hpp>
#include <scene/scene.hpp>

#include <optional>
#include <memory>


namespace engine
{
    class base_window;
    class keyboard_input_manager;
    class mouse_input_manager;

    class engine_impl
    {
    public:
        engine_impl(std::unique_ptr<interfaces::scene_renderer>);
        virtual void init_window(int32_t, int32_t, std::string) = 0;
        virtual void exec() = 0;
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
        virtual ~engine_impl();

        template <typename scene_t>
        void set_scene(scene_t&& scene)
        {
            m_scene = std::move(scene);
        }

    protected:
        std::unique_ptr<base_window> m_window;
        scene m_scene;
        assets_manager m_assets_manager;
        std::unique_ptr<keyboard_input_manager> m_keyboard_manager;
        std::unique_ptr<mouse_input_manager> m_mouse_manager;
    };
}

