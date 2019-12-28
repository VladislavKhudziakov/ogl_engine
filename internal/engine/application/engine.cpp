//
// Created by movleaxedx on 23.12.19.
//

#include <ogl_engine.hpp>
#include <engine_impl.hpp>
#include <engine.hpp>

#define OGL_ENGINE

engine::rendering_engine::rendering_engine()
#if defined(OGL_ENGINE)
 : p_impl{std::make_unique<ogl_engine>()}
#else
    #error "UNSUPPORTED OR UNDEFINED ENGINE TYPE"
#endif
{
}

engine::rendering_engine::~rendering_engine() = default;

void engine::rendering_engine::init_window(int32_t w, int32_t h, const std::string& name)
{
    p_impl->init_window(w, h, name);
}


void engine::rendering_engine::exec()
{
    p_impl->exec();
}


const engine::keyboard_input_manager& engine::rendering_engine::get_keyboard_manager() const
{
    return p_impl->get_keyboard_manager();
}


const engine::mouse_input_manager& engine::rendering_engine::get_mouse_manager() const
{
    return p_impl->get_mouse_manager();
}


engine::keyboard_input_manager& engine::rendering_engine::get_keyboard_manager()
{
    return p_impl->get_keyboard_manager();
}


engine::mouse_input_manager& engine::rendering_engine::get_mouse_manager()
{
    return p_impl->get_mouse_manager();
}


const engine::scene& engine::rendering_engine::get_scene() const
{
    return p_impl->get_scene();
}


engine::scene& engine::rendering_engine::get_scene()
{
    return p_impl->get_scene();
}


engine::assets_manager& engine::rendering_engine::get_assets_manager()
{
    return p_impl->get_assets_manager();
}


const engine::assets_manager& engine::rendering_engine::get_assets_manager() const
{
    return p_impl->get_assets_manager();
}


const engine::base_window& engine::rendering_engine::get_window() const
{
    return p_impl->get_window();
}


engine::base_window& engine::rendering_engine::get_window()
{
    return p_impl->get_window();
}
