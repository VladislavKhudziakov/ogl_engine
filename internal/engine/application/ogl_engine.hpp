//
// Created by movleaxedx on 10.10.19.
//

#pragma once

#include <string>
#include <memory>
#include <GLFW/glfw3.h>
#include <engine_impl.hpp>

//TODO: add input events system
namespace engine
{

    class ogl_engine : public engine_impl
    {
    public:
        ogl_engine();
        ~ogl_engine() override = default;
        void init_window(int32_t, int32_t, std::string) override;
        void exec() override;
        void set_scene(std::unique_ptr<scene>);
    private:
    };
} // namespace engine
