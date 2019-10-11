//
// Created by Vladislav Khudiakov on 10/11/19.
//
#include <glad/glad.h>

#include "scene_object.hpp"


engine::scene_object::scene_object(std::unique_ptr<engine::mesh> mesh, const engine::shader_program& program)
    : mesh(std::move(mesh))
    , program(program)
{
}


void engine::scene_object::draw(glm::mat4 mvp)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    program.bind();
    program.apply_uniform_command(engine::set_mat4_uniform("u_mvp", mvp));
    mesh->draw();
    program.unbind();
}

