//
// Created by movleaxedx on 5.12.19.
//


#pragma once

#include <application/keyboard_input_manager.hpp>

namespace engine
{
    struct key_event
    {
        keyboard_input_manager::KEYBOARD_EVENT event_type;
        keyboard_input_manager::KEY_CODE key;
    };

}
