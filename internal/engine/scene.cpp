//
// Created by movleaxedx on 10.10.19.
//

#include <glad/glad.h>

#include <scene.hpp>



void engine::scene::set_mesh(std::unique_ptr<mesh> mesh)
{
  m_mesh = std::move(mesh);
}



void engine::scene::draw()
{
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);
  m_mesh->draw();
}