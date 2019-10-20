//
// Created by movleaxedx on 10.10.19.
//

#include <glad/glad.h>

#include <scene/scene.hpp>


//TODO: think over how to set aspect dynamicly

using glm::vec3;
using engine::camera;

engine::scene::scene()
    : m_camera{camera(vec3(5.0f, 5.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), 60.0f)}
    , m_perspective{1, 100}
    , m_projection_matrix()
    , m_view_matrix()
    , m_projection_view()
{
    calculate_matrices();
}


void engine::scene::set_object(std::shared_ptr<scene_object> obj)
{
    m_object = std::move(obj);
}


void engine::scene::draw()
{
    //TODO: remove
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_object->draw(m_projection_view);
}


void engine::scene::set_camera(const camera& camera)
{
    m_camera = camera;
    m_view_matrix = glm::lookAt(m_camera.get_position(), m_camera.get_direction(), glm::vec3(0, 1, 0));
    calculate_matrices();
    //TODO: add signal
}


const engine::camera& engine::scene::get_camera() const
{
    return m_camera;
}


void engine::scene::set_perspective(const engine::perspective& perspective)
{
    m_perspective = perspective;
    calculate_matrices();
    //TODO: add signal
}


const engine::perspective& engine::scene::get_perspective() const
{
    return m_perspective;
}


void engine::scene::calculate_matrices()
{
    auto fov = glm::radians(m_camera.get_fov());
    m_projection_matrix = glm::perspective(fov, 800.0f / 600.0f, m_perspective.get_znear(), m_perspective.get_zfar());
    m_view_matrix = glm::lookAt(m_camera.get_position(), m_camera.get_direction(), glm::vec3(0, 1, 0));
    m_projection_view = m_projection_matrix * m_view_matrix;
}
