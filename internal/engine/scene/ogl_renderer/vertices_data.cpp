//
// Created by movleaxedx on 29.12.19.
//

#include <scene/ogl_renderer/vertices_data.hpp>
#include <glad/glad.h>


engine::ogl::vertices_data::vertices_data()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


const engine::ogl::vertex_array_object& engine::ogl::vertices_data::get_vertices_buffer() const
{
    return m_vao;
}


const engine::ogl::buffer_object& engine::ogl::vertices_data::get_indices_buffer() const
{
    return m_ebo;
}


std::unique_ptr<engine::ogl::vertices_data>
engine::ogl::vertices_data::from_geometry(const engine::geometry& geometry)
{
    const auto& vertices = geometry.get_vertices();
    const auto& faces = geometry.get_faces();
    auto gpu_data = std::make_unique<ogl::vertices_data>();

    std::vector<int32_t> indices;

    for(const auto& face : faces) {
        std::copy(face.indices.begin(), face.indices.end(), std::back_inserter(indices));
    }

    glBindVertexArray(gpu_data->get_vertices_buffer());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpu_data->get_indices_buffer());

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int32_t), &indices.front(), GL_STATIC_DRAW);

    buffer_object vertices_gpu_buffer;
    glBindBuffer(GL_ARRAY_BUFFER, vertices_gpu_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(sizeof(vertex::position)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(sizeof(vertex::position) + sizeof(vertex::uv)));

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return std::move(gpu_data);
}
