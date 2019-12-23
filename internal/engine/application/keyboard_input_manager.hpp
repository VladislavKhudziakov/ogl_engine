//
// Created by movleaxedx on 5.12.19.
//


#pragma once

#include <boost/signals2/signal.hpp>

namespace engine
{
    class key_event;

    class keyboard_input_manager
    {
    public:
        using connection_t = boost::signals2::connection;

        virtual ~keyboard_input_manager() = default;

        // clang-format off
        enum class KEY_CODE {
            SPACE = 0x20,
            A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            a = 0x61, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
        };
        // clang-format on

        enum class KEYBOARD_EVENT {
            PRESS, RELEASE, HOLD
        };

        connection_t subscribe_event_handler(const std::function<void(const key_event&)>&);

    protected:
        boost::signals2::signal<void(const key_event&)> m_key_event_signal;
    };
} // namespace engine::ogl_engine
