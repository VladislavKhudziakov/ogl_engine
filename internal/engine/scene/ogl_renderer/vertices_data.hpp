//
// Created by movleaxedx on 29.12.19.
//


#pragma once

#include <memory>

#include <assets/geometry.hpp>
#include <scene/ogl_renderer/buffers/vertex_array_object.hpp>
#include <scene/ogl_renderer/buffers/buffer_object.hpp>

namespace engine::ogl
{
    class vertices_data
    {
    public:
        static std::unique_ptr<vertices_data> from_geometry(const geometry&);

        vertices_data();
        ~vertices_data() = default;
        const vertex_array_object& get_vertices_buffer() const;
        const buffer_object& get_indices_buffer() const;

    private:
        vertex_array_object m_vao;
        buffer_object m_ebo;
    };
} // namespace engine::ogl
