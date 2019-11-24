//
// Created by movleaxedx on 10.10.19.
//

#pragma once

#include <memory>
#include <vector>

#include <scene/camera.hpp>
#include <scene/perspective.hpp>
#include <scene/interfaces/scene_renderer.hpp>
#include <scene/light_source.hpp>

namespace engine
{
    class scene_object;

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
        void add_light_source(const engine::light_source&);
        const std::vector<engine::light_source>& get_light_sources() const;

        template <typename T>
        void acquire_gpu_resource(const std::shared_ptr<T>& resource)
        {
              m_renderer->acquire_gpu_resource(resource);
        }

        template <typename T>
        void release_gpu_resource(const std::shared_ptr<T>& resource)
        {
            m_renderer->release_gpu_resource(resource);
        }

    private:
        std::shared_ptr<engine::scene_object> m_root;
        camera m_camera;
        perspective m_perspective;
        std::shared_ptr<interfaces::scene_renderer> m_renderer;
        std::vector<engine::light_source> m_light_sources;
    };
} // namespace engine
