//
// Created by movleaxedx on 23.12.19.
//

#include <application/base_window.hpp>
#include <application/keyboard_input_manager.hpp>
#include <application/mouse_input_manager.hpp>
#include <application/engine_impl.hpp>

engine::engine_impl::engine_impl(std::unique_ptr<interfaces::scene_renderer> renderer)
    : m_scene{std::move(renderer)}
{
}

engine::engine_impl::~engine_impl() = default;

const engine::keyboard_input_manager& engine::engine_impl::get_keyboard_manager() const
{
    return *m_keyboard_manager;
}

const engine::mouse_input_manager& engine::engine_impl::get_mouse_manager() const
{
    return *m_mouse_manager;
}

engine::keyboard_input_manager& engine::engine_impl::get_keyboard_manager()
{
    return *m_keyboard_manager;
}

engine::mouse_input_manager& engine::engine_impl::get_mouse_manager()
{
    return *m_mouse_manager;
}

const engine::scene& engine::engine_impl::get_scene() const
{
    return m_scene;
}

engine::scene& engine::engine_impl::get_scene()
{
    return m_scene;
}

engine::assets_manager& engine::engine_impl::get_assets_manager()
{
    return m_assets_manager;
}

const engine::assets_manager& engine::engine_impl::get_assets_manager() const
{
    return m_assets_manager;
}

const engine::base_window& engine::engine_impl::get_window() const
{
    return *m_window;
}

engine::base_window& engine::engine_impl::get_window()
{
    return *m_window;
}
