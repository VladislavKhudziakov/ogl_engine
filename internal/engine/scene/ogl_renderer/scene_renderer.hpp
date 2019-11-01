//
// Created by movleaxedx on 29.10.19.
//


#pragma once

#include <scene.hpp>
#include <scene/interfaces/scene_renderer.hpp>
#include <scene/ogl_renderer/gpu_cache.hpp>
#include <scene/components/interfaces/component_visitor.hpp>


namespace engine::ogl
{
    class scene_renderer : public engine::interfaces::scene_renderer, public engine::interfaces::component_visitor
    {
    public:
        explicit scene_renderer(scene*);
        scene_renderer() = default;
        ~scene_renderer() override = default;
        void set_scene(scene*) override;
        void draw_scene() override;

        void accept(material_component& component, std::shared_ptr<scene_object>& ptr) override;
        void accept(mesh_instance& instance, std::shared_ptr<scene_object>& ptr) override;
        void accept(transformation& transformation, std::shared_ptr<scene_object>& ptr) override;

        void process_nodes(std::shared_ptr<scene_object>);

    private:
        void cache_material(const std::shared_ptr<material>&);
        void bind_material(const std::shared_ptr<material>&);
        void release_material(const std::shared_ptr<material>&);
        void cache_geometry(const std::shared_ptr<geometry>&);
        void draw_geometry(const std::shared_ptr<geometry>&);

        //TODO: replace on weak_ptr
        engine::scene* m_scene = nullptr;
        gpu_cache m_cache;
        glm::mat4 m_view_matrix{1};
        glm::mat4 m_projection_matrix{1};
        glm::mat4 m_world_matrix{1};
    };
} // namespace engine::ogl
