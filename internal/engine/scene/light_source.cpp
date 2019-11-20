//
// Created by movleaxedx on 3.11.19.
//

#include <scene/light_source.hpp>


engine::light_source::light_source(const glm::vec3& position, const glm::vec3& color)
    : m_position(position)
    , m_color(color)
{
}


const glm::vec3& engine::light_source::get_position() const
{
    return m_position;
}


const glm::vec3& engine::light_source::get_color() const
{
    return m_color;
}


void engine::light_source::set_position(const glm::vec3& position)
{
    m_position = position;
}


void engine::light_source::set_color(const glm::vec3& color)
{
    m_color = color;
}
