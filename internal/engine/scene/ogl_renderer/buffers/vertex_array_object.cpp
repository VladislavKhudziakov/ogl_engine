//
// Created by movleaxedx on 29.12.19.
//

#include <glad/glad.h>

#include <cassert>
#include <algorithm>

#include <scene/ogl_renderer/buffers/vertex_array_object.hpp>


engine::ogl::vertex_array_object::vertex_array_object()
    : m_name(0)
{
    glGenVertexArrays(1, &m_name);
}


engine::ogl::vertex_array_object::~vertex_array_object()
{
    glDeleteVertexArrays(1, &m_name);
}


engine::ogl::vertex_array_object::vertex_array_object(engine::ogl::vertex_array_object&& src) noexcept
    : m_name(0)
{
    *this = std::move(src);
}


engine::ogl::vertex_array_object& engine::ogl::vertex_array_object::operator=(engine::ogl::vertex_array_object&& src) noexcept
{
    assert(this != &src);

    m_name = src.m_name;
    src.m_name = 0;

    return *this;
}


engine::ogl::vertex_array_object::operator uint32_t() const
{
    return m_name;
}
