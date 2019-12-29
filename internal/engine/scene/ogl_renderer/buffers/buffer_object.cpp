//
// Created by movleaxedx on 29.12.19.
//

#include <glad/glad.h>
#include <cassert>
#include <scene/ogl_renderer/buffers/buffer_object.hpp>
#include <algorithm>


engine::ogl::buffer_object::buffer_object()
    : m_name(0)
{
    glGenBuffers(1, &m_name);
}


engine::ogl::buffer_object::~buffer_object()
{
    glDeleteBuffers(1, &m_name);
}


engine::ogl::buffer_object::buffer_object(engine::ogl::buffer_object&& src) noexcept
    : m_name(0)
{
    *this = std::move(src);
}


engine::ogl::buffer_object& engine::ogl::buffer_object::operator=(engine::ogl::buffer_object&& src) noexcept
{
    assert(this != &src);

    m_name = src.m_name;
    src.m_name = 0;

    return *this;
}


engine::ogl::buffer_object::operator uint32_t() const
{
    return m_name;
}
