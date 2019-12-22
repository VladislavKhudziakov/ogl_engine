//
// Created by movleaxedx on 22.12.19.
//

#include <mouse_input_manager.hpp>


engine::mouse_input_manager::connection_t
engine::mouse_input_manager::subscribe_cursor_position_handler(
    const std::function<void(double, double)>& handler)
{
    return on_cursor_position_changed.connect(handler);
}


engine::mouse_input_manager::connection_t
engine::mouse_input_manager::subscribe_buttons_handler(
    const std::function<void(MOUSE_BUTTON, MOUSE_EVENT)>& handler)
{
    return on_button_pressed.connect(handler);
}
