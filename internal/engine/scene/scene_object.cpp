//
// Created by Vladislav Khudiakov on 10/11/19.
//
#include <algorithm>
#include <scene_object.hpp>


engine::scene_object::scene_object(const std::string& name)
    : m_name(name)
{
    set_component<transformation>(std::make_shared<transformation>());
}


std::string engine::scene_object::get_name() const
{
    return m_name;
}


std::shared_ptr<engine::scene_object> engine::scene_object::get_parent() const
{
    return m_parent.lock();
}


void engine::scene_object::set_parent(const std::shared_ptr<scene_object>& parent)
{
    m_parent = parent;
}


engine::scene_object& engine::scene_object::add_child(std::shared_ptr<scene_object> object)
{
    object->set_parent(shared_from_this());
    m_children.emplace_back(std::move(object));
    return *this;
}


engine::scene_object& engine::scene_object::remove_child(const std::string& name)
{
    auto founded_object = std::find_if(m_children.begin(), m_children.end(), [&](auto& object) {
        return object->get_name() == name;
    });

    if (founded_object != m_children.end()) {
        m_children.erase(founded_object);
    }

    return *this;
}


const std::vector<std::shared_ptr<engine::scene_object>>& engine::scene_object::get_children()
{
    return m_children;
}


const std::vector<std::shared_ptr<engine::scene_object>>& engine::scene_object::get_children() const
{
    return m_children;
}


const engine::scene_object::components& engine::scene_object::get_components() const
{
    return m_components;
}


void engine::scene_object::set_transformation_matrix(glm::mat4 matrix)
{
    m_transformation_matrix = matrix;
}


glm::mat4 engine::scene_object::get_transformation_matrix() const
{
    return m_transformation_matrix;
}
