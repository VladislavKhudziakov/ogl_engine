//
// Created by Vladislav Khudiakov on 10/8/19.
//

#include "mesh.hpp"
#include <glad/glad.h>


engine::mesh::mesh()
    : vao(0)
    , ebo(0)
    , indices_count(0)
{
}


engine::mesh::~mesh()
{
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}


void engine::mesh::draw() const
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


engine::mesh_builder::mesh_builder()
    : m_mesh(new engine::mesh)
{
}


engine::mesh_builder& engine::mesh_builder::create_default(const std::vector<mesh::vertex>& vertices, const ::std::vector<int>& indices)
{
    uint32_t vao, ebo, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(mesh::vertex), &vertices.begin()->position[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &*indices.begin(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mesh::vertex), reinterpret_cast<void*>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(mesh::vertex), reinterpret_cast<void*>(sizeof(mesh::vertex::position)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(mesh::vertex), reinterpret_cast<void*>(sizeof(mesh::vertex::position) + sizeof(mesh::vertex::uv)));

    m_mesh->vao = vao;
    m_mesh->ebo = ebo;
    m_mesh->indices_count = indices.size();

    vbo_list.emplace_back(vbo);
    return *this;
}


std::unique_ptr<engine::mesh> engine::mesh_builder::generate_mesh()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(vbo_list.size(), &*vbo_list.begin());

    return std::move(m_mesh);
}


std::unique_ptr<engine::mesh> engine::mesh_builder::generate_default_mesh(
    const std::vector<mesh::vertex>& vertices,
    const ::std::vector<int>& indices)
{
    create_default(vertices, indices);
    return generate_mesh();
}


engine::mesh_builder& engine::mesh_builder::append_buffer(
    const engine::mesh_builder::add_buffer_command_base& command)
{
    command.execute();
    vbo_list.emplace_back(command.buffer);
    return *this;
}
