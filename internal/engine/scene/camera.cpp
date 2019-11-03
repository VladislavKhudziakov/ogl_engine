//
// Created by Vladislav Khudiakov on 10/11/19.
//


#include "camera.hpp"


engine::camera::camera(const glm::vec3& position, const glm::vec3& look_direction, float fov)
    : m_position(position)
    , m_look_direction(look_direction)
    , m_fov(fov)
{
}


void engine::camera::set_direction(glm::vec3 direction)
{
    m_look_direction = direction;
}


void engine::camera::set_position(glm::vec3 position)
{
    m_position = position;
}


void engine::camera::set_fov(float fov)
{
    m_fov = fov;
}


glm::vec3 engine::camera::get_direction() const
{
    return m_look_direction;
}


glm::vec3 engine::camera::get_position() const
{
    return m_position;
}


float engine::camera::get_fov()
{
    return m_fov;
}
