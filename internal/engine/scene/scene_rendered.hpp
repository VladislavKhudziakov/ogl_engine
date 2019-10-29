//
// Created by movleaxedx on 29.10.19.
//


#pragma once

#include <scene.hpp>
#include <components/interfaces/component_visitor.hpp>

namespace engine
{
    class scene_rendered : public interfaces::component_visitor
    {
    public:
        explicit scene_rendered(std::shared_ptr<scene>);
        ~scene_rendered() override = default;
        void draw_scene();
        void process_nodes(std::shared_ptr<scene_object>);
        void accept(material_component& component, std::shared_ptr<scene_object>& ptr) override;
        void accept(mesh_instance& instance, std::shared_ptr<scene_object>& ptr) override;
        void accept(transformation& transformation, std::shared_ptr<scene_object>& ptr) override;

    private:
        std::weak_ptr<engine::scene> m_scene;
        glm::mat4 m_view_matrix {1};
        glm::mat4 m_projection_matrix {1};
        glm::mat4 m_world_matrix {1};
    };
}

