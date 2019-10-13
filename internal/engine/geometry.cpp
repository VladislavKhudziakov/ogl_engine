//
// Created by Vladislav Khudiakov on 10/8/19.
//

#include <geometry.hpp>
#include <stdexcept>
#include <glad/glad.h>


engine::geometry::geometry()
    : vao(0)
    , ebo(0)
    , indices_count(0)
{
}


engine::geometry::~geometry()
{
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}


void engine::geometry::draw() const
{
    if (!is_bounded) {
        throw std::logic_error("GEOMETRY IS NOT BOUNDED");
    }

    glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);
}


void engine::geometry::bind()
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    is_bounded = true;
    //TODO: ADD LOCK CONTEXT !!!!
    //// template class with static is_bounded?
}


void engine::geometry::unbind()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    is_bounded = false;
}


engine::geometry_builder::geometry_builder()
    : m_geometry(new engine::geometry)
{
}


engine::geometry_builder& engine::geometry_builder::create_default(const std::vector<engine::geometry::vertex>& vertices, const ::std::vector<int>& indices)
{
    uint32_t vao, ebo, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(geometry::vertex), &vertices.begin()->position[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &*indices.begin(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(geometry::vertex), reinterpret_cast<void*>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(geometry::vertex), reinterpret_cast<void*>(sizeof(geometry::vertex::position)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(geometry::vertex), reinterpret_cast<void*>(sizeof(geometry::vertex::position) + sizeof(geometry::vertex::uv)));

    m_geometry->vao = vao;
    m_geometry->ebo = ebo;
    m_geometry->indices_count = indices.size();

    vbo_list.emplace_back(vbo);
    return *this;
}


std::shared_ptr<engine::geometry> engine::geometry_builder::generate_mesh()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(vbo_list.size(), &*vbo_list.begin());

    return m_geometry;
}


std::shared_ptr<engine::geometry> engine::geometry_builder::generate_default_mesh(
    const std::vector<geometry::vertex>& vertices,
    const std::vector<int>& indices)
{
    create_default(vertices, indices);
    return generate_mesh();
}


engine::geometry_builder& engine::geometry_builder::append_buffer(
    const engine::geometry_builder::add_buffer_command_base& command)
{
    command.execute();
    vbo_list.emplace_back(command.buffer);
    return *this;
}


void engine::append_float_buffer::execute() const
{
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &*data.begin(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(shader_location);
    glVertexAttribPointer(shader_location, 1, GL_FLOAT, GL_FALSE, sizeof(float), reinterpret_cast<void*>(0));
}
