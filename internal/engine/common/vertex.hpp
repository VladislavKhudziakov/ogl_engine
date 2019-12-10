//
// Created by movleaxedx on 2.11.19.
//


#pragma once

#include <vector>
#include <vectors.hpp>

namespace engine
{
    struct vertex
    {
        vertex(float x, float y, float z, float u, float v, float n_x, float n_y, float n_z)
            : position{x, y, z}
            , uv{u, v}
            , normal{n_x, n_y, n_z}
        {
        }

        vec3 position;
        vec2 uv;
        vec3 normal;
    };

    struct face
    {
        std::vector<uint32_t> indices;
    };
} // namespace engine
