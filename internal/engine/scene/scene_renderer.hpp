//
// Created by movleaxedx on 29.10.19.
//


#pragma once

#include <scene.hpp>
#include <components/interfaces/component_visitor.hpp>
#include <interfaces/scene_renderer.hpp>

namespace engine
{
    class scene_renderer : public interfaces::scene_renderer, public interfaces::component_visitor
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
        engine::scene* m_scene = nullptr;
        glm::mat4 m_view_matrix {1};
        glm::mat4 m_projection_matrix {1};
        glm::mat4 m_world_matrix {1};
    };
}

