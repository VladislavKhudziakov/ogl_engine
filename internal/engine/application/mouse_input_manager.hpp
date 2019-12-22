//
// Created by movleaxedx on 22.12.19.
//


#pragma once

#include <boost/signals2/signal.hpp>

namespace engine
{
    class mouse_input_manager
    {
    public:
        enum class MOUSE_EVENT
        {
            PRESS,
            RELEASE
        };

        // clang-format off
        enum class MOUSE_BUTTON
        {
            LEFT, RIGHT, CENTER, _4, _5, _6, _7, _8
        };
        // clang-format on

        //todo mose mode

        using connection_t = boost::signals2::connection;
        virtual ~mouse_input_manager() = default;
        connection_t subscribe_cursor_position_handler(const std::function<void(double, double)>&);
        connection_t subscribe_buttons_handler(const std::function<void(MOUSE_BUTTON, MOUSE_EVENT)>&);

    protected:
        boost::signals2::signal<void(double, double)> on_cursor_position_changed;
        boost::signals2::signal<void(MOUSE_BUTTON, MOUSE_EVENT)> on_button_pressed;
    };
} // namespace engine
