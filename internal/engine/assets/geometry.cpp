//
// Created by Vladislav Khudiakov on 10/8/19.
//

#include <geometry.hpp>
#include <interfaces/geometry_buffer.hpp>
#include <stdexcept>
#include <glad/glad.h>


engine::geometry::geometry(const std::vector<engine::geometry::vertex>& vertices, const ::std::vector<int>& indices)
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

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(geometry::vertex), &vertices.begin()->position[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &*indices.begin(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(geometry::vertex), reinterpret_cast<void*>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(geometry::vertex), reinterpret_cast<void*>(sizeof(geometry::vertex::position)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(geometry::vertex), reinterpret_cast<void*>(sizeof(geometry::vertex::position) + sizeof(geometry::vertex::uv)));

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);
}


engine::geometry::~geometry()
{
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}


void engine::geometry::draw() const
{
    glDrawElements(GL_TRIANGLES, m_indices_count, GL_UNSIGNED_INT, nullptr);
}


void engine::geometry::bind()
{
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}


void engine::geometry::unbind()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


engine::float_buffer::float_buffer(int32_t slot, std::vector<float>& values, std::shared_ptr<interfaces::geometry_buffer> geometry)
    : m_wrappee(std::move(geometry))
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


void engine::float_buffer::bind()
{
    m_wrappee->bind();
}


void engine::float_buffer::unbind()
{
    m_wrappee->unbind();
}


void engine::float_buffer::draw() const
{
    m_wrappee->draw();
}
