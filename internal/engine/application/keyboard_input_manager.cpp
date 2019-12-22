//
// Created by movleaxedx on 5.12.19.
//

#include <application/keyboard_input_manager.hpp>
#include <application/key_event.hpp>


using namespace engine;

keyboard_input_manager::connection_t keyboard_input_manager::subscribe_event_handler(
    const std::function<void(const key_event&)>& handler)
{
    return m_key_event_signal.connect(handler);
}
