//
// Created by movleaxedx on 29.10.19.
//


#pragma once

#include <scene.hpp>
#include <scene/interfaces/scene_renderer.hpp>
#include <scene/ogl_renderer/gpu_cache.hpp>
#include <scene/components/interfaces/component_visitor.hpp>
#include <assets/types.hpp>

namespace engine::ogl
{
    class scene_renderer : public engine::interfaces::scene_renderer, public engine::interfaces::component_visitor
    {
    public:
        friend class gpu_cache_resolver;

        explicit scene_renderer(scene*);
        scene_renderer() = default;
        scene_renderer(const scene_renderer&) = delete;
        scene_renderer(scene_renderer&&) = default;
        const scene_renderer& operator=(const scene_renderer&) = delete;
        scene_renderer& operator=(scene_renderer&&) = default;
        ~scene_renderer() override = default;

        void set_scene(scene*) override;
        void draw_scene() override;

        void accept(mesh_instance& instance, std::shared_ptr<scene_object>& ptr) override;
        void accept(transformation& transformation, std::shared_ptr<scene_object>& ptr) override;

    private:
    public:
        void acquire_gpu_resource(const std::shared_ptr<engine::interfaces::component>& ptr) override;
        void release_gpu_resource(const std::shared_ptr<engine::interfaces::component>& ptr) override;

    private:
        void process_nodes(std::shared_ptr<scene_object>);
        void bind_material(const assets::material_t&);
        void release_material(const assets::material_t&);
        void draw_geometry(const assets::geometry_t&);

        //TODO: replace on weak_ptr
        engine::scene* m_scene = nullptr;
        gpu_cache m_cache;
        glm::mat4 m_view_matrix{1};
        glm::mat4 m_projection_matrix{1};
        glm::mat4 m_world_matrix{1};
    };
} // namespace engine::ogl
