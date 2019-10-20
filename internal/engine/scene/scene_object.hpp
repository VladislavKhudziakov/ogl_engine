//
// Created by Vladislav Khudiakov on 10/11/19.
//

#pragma once

#include <memory>

#include <mesh_instance.hpp>
#include <material.hpp>
#include <shader_program.hpp>
#include <glm/glm.hpp>

namespace engine
{
    class scene_object : public std::enable_shared_from_this<scene_object>
    {
    public:
        explicit scene_object(const std::string&);
        virtual ~scene_object() = default;

        std::string get_name() const;
        scene_object& add_child(std::shared_ptr<scene_object>);
        scene_object& remove_child(const std::string&);

        std::shared_ptr<scene_object> get_parent() const;
        void set_parent(const std::shared_ptr<scene_object>&);

        const std::vector<std::shared_ptr<scene_object>>& get_children();
        const std::vector<std::shared_ptr<scene_object>>& get_children() const;

        virtual void draw(glm::mat4) const;

    protected:
        std::string m_name;
        std::weak_ptr<scene_object> m_parent;
        std::vector<std::shared_ptr<scene_object>> m_children;
    };
} // namespace engine
