//
// Created by movleaxedx on 29.10.19.
//


#pragma once

namespace engine
{
    class scene;
}


namespace engine::interfaces
{
    class scene_renderer
    {
    public:
        virtual ~scene_renderer() = default;
        virtual void draw_scene() = 0;
        virtual void set_scene(scene*) = 0;
    };
}

