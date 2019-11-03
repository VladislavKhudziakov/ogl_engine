//
// Created by movleaxedx on 10.10.19.
//


#include <scene/scene.hpp>
#include <iostream>

//TODO: think over how to set aspect dynamicly

using glm::vec3;
using engine::camera;

engine::scene::scene(std::shared_ptr<interfaces::scene_renderer> renderer)
    : m_camera{camera(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), 60.0f)}
    , m_perspective{1, 100}
    , m_renderer(std::move(renderer))
{
    m_renderer->set_scene(this);
}


void engine::scene::draw()
{
    m_renderer->draw_scene();
}


void engine::scene::set_camera(const camera& camera)
{
    m_camera = camera;
}


const engine::camera& engine::scene::get_camera() const
{
    return m_camera;
}


void engine::scene::set_perspective(const engine::perspective& perspective)
{
    m_perspective = perspective;
}


const engine::perspective& engine::scene::get_perspective() const
{
    return m_perspective;
}



void engine::scene::set_root(std::shared_ptr<scene_object> root)
{
    m_root = std::move(root);
}


std::shared_ptr<engine::scene_object> engine::scene::get_root()
{
    return m_root;
}
