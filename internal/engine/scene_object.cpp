//
// Created by Vladislav Khudiakov on 10/11/19.
//
#include <glad/glad.h>

#include "scene_object.hpp"
#include "bind_context.hpp"


engine::scene_object::scene_object(std::shared_ptr<mesh_instance> mesh, const engine::shader_program& program)
    : m_mesh(std::move(mesh))
    , program(program)
{
}


void engine::scene_object::draw(glm::mat4 mvp)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    engine::bind_context bind(program);
    program.apply_uniform_command(engine::set_mat4_uniform("u_mvp", mvp));
    m_mesh->draw();
}

