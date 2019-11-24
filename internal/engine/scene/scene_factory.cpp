//
// Created by movleaxedx on 24.11.19.
//

#include <scene/scene.hpp>
#include <scene/scene_object.hpp>
#include <scene/scene_factory.hpp>

engine::scene_factory::scene_factory(engine::scene& scene)
    : m_scene_ref(scene)
{
}


std::shared_ptr<engine::scene_object> engine::scene_factory::make_scene_object(const std::string& name)
{
    return std::make_shared<scene_object>(m_scene_ref, name);
}
