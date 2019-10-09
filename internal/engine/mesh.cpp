//
// Created by Vladislav Khudiakov on 10/8/19.
//

#include "mesh.hpp"
#include <glad/glad.h>


engine::mesh::mesh(const std::vector<mesh::vertex> &vertices,
    const::std::vector<int>& indices) : vao(0), ebo(0), indices_count(indices.size())
{
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  uint32_t vbo;

  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(mesh::vertex),
      &vertices.begin()->position[0], GL_STATIC_DRAW);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
      &*indices.begin(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mesh::vertex),
      reinterpret_cast<void*>(0));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(mesh::vertex),
      reinterpret_cast<void*>(sizeof(mesh::vertex::position)));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(mesh::vertex),
      reinterpret_cast<void*>(sizeof(mesh::vertex::position) + sizeof(mesh::vertex::uv)));

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vbo);
}


engine::mesh::~mesh()
{
//  glDeleteBuffers(1, &ebo);
//  glDeleteVertexArrays(1, &vao);
}


void engine::mesh::draw() const
{
  glBindVertexArray(vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
