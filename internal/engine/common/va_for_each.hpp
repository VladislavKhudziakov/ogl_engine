//
// Created by movleaxedx on 28.12.19.
//


#pragma once

namespace engine
{
    template<typename function_t, typename arg_t, typename... args_t>
    void va_for_each(function_t&& callback, arg_t&& current_argument, args_t&& ...arguments)
    {
        callback(std::forward<arg_t>(current_argument));

        if constexpr (sizeof...(arguments) == 0) {
            return;
        }

        va_for_each(std::forward(callback), std::forward<args_t>(arguments)...);
    }
} // namespace engine
