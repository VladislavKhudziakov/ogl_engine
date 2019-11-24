//
// Created by movleaxedx on 29.10.19.
//


#pragma once

#include <memory>


namespace engine
{
    class scene;
}


namespace engine::interfaces
{
    class component;
}


namespace engine::interfaces
{
    class scene_renderer
    {
    public:
        virtual ~scene_renderer() = default;
        virtual void draw_scene() = 0;
        virtual void set_scene(scene*) = 0;
        virtual void acquire_gpu_resource(const std::shared_ptr<component>&) = 0;
        virtual void release_gpu_resource(const std::shared_ptr<component>&) = 0;
    };
}

