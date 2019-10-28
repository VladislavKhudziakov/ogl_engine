//
// Created by Vladislav Khudiakov on 10/11/19.
//

#pragma once

#include <memory>
#include <optional>
#include <tuple>

#include <mesh_data.hpp>
#include <material.hpp>
#include <shader_program.hpp>
#include <glm/glm.hpp>
#include <components/transformation.hpp>
#include <scene/components/mesh_instance.hpp>
#include <scene/components/material_component.hpp>

namespace engine
{
    class scene_object : public std::enable_shared_from_this<scene_object>
    {
        using components = std::tuple<std::shared_ptr<transformation>, std::shared_ptr<mesh_instance>, std::shared_ptr<material_component>>;

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

        void set_transformation_matrix(glm::mat4);
        glm::mat4 get_transformation_matrix() const;

        const components& get_components() const;

        template<typename T>
        std::shared_ptr<T> get_component() const
        {
            return std::get<std::shared_ptr<T>>(m_components);
        }


        template<typename T>
        void set_component(std::shared_ptr<T> component)
        {
            std::get<std::shared_ptr<T>>(m_components) = component;
        }


    protected:
        std::string m_name;
        std::weak_ptr<scene_object> m_parent;
        std::vector<std::shared_ptr<scene_object>> m_children;
        glm::mat4 m_transformation_matrix;
        components m_components;
    };
} // namespace engine
