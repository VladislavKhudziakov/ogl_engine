//
// Created by movleaxedx on 31.10.19.
//

#include <glad/glad.h>

#include <scene/ogl_renderer/vertex_buffer.hpp>


engine::ogl::vertex_buffer::vertex_buffer(const std::vector<vertex>& vertices, const std::vector<uint32_t>& indices)
    : m_vao(0)
    , m_ebo(0)
    , m_indices_count(indices.size())
{
    uint32_t vbo;

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_ebo);
    glGenBuffers(1, &vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices.begin()->position.x, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &*indices.begin(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(sizeof(vertex::position)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(sizeof(vertex::position) + sizeof(vertex::uv)));

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);
}


void engine::ogl::vertex_buffer::bind()
{
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}


void engine::ogl::vertex_buffer::unbind()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


engine::ogl::vertex_buffer::~vertex_buffer()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_ebo);
}


engine::ogl::float_buffer::float_buffer(int32_t slot, std::vector<float>& values, std::shared_ptr<ogl::interfaces::vertex_buffer> wrapee)
    : m_wrappee(std::move(wrapee))
{
    m_wrappee->bind();

    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(float), &*values.begin(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(slot);
    glVertexAttribPointer(slot, 1, GL_FLOAT, GL_FALSE, sizeof(float), reinterpret_cast<void*>(0));

    m_wrappee->unbind();
    glDeleteBuffers(1, &vbo);
}


void engine::ogl::float_buffer::bind()
{
    m_wrappee->bind();
}


void engine::ogl::float_buffer::unbind()
{
    m_wrappee->unbind();
}
