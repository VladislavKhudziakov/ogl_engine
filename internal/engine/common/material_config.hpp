//
// Created by movleaxedx on 20.11.19.
//


#pragma once

namespace engine
{
    struct material_config
    {
        enum class culling_type {
            none, front, back
        };

        enum class blend_mode {
            none, alpha, add, multiply
        };

        culling_type culling = culling_type::back;
        blend_mode blending = blend_mode::none;

        bool write_color = true;
        bool enable_depth_test = true;
    };
}

