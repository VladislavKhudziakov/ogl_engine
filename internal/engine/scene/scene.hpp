//
// Created by movleaxedx on 10.10.19.
//

#pragma once

#include <memory>

#include <scene/scene_object.hpp>
#include <scene/camera.hpp>
#include <scene/perspective.hpp>
#include <scene/interfaces/scene_renderer.hpp>


namespace engine
{
    class scene
    {
    public:
        explicit scene(std::shared_ptr<interfaces::scene_renderer>);
        ~scene() = default;

        void draw();
        void set_root(std::shared_ptr<scene_object>);
        std::shared_ptr<scene_object> get_root();

        void set_camera(const camera&);
        void set_perspective(const perspective&);
        const camera& get_camera() const;
        const perspective& get_perspective() const;

    private:
        std::shared_ptr<engine::scene_object> m_root;
        camera m_camera;
        perspective m_perspective;
        std::shared_ptr<interfaces::scene_renderer> m_renderer;
    };
} // namespace engine
