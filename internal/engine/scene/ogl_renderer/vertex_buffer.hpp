//
// Created by movleaxedx on 31.10.19.
//


#pragma once

#include <common/vectors.hpp>
#include <scene/ogl_renderer/interfaces/vertex_buffer.hpp>

#include <vector>
#include <cstdint>
#include <memory>

namespace engine::ogl
{
    class vertex_buffer : public ogl::interfaces::vertex_buffer
    {
    public:
        struct vertex
        {
            vec3 position;
            vec2 uv;
            vec3 normal;
        };

        vertex_buffer(const std::vector<vertex>&, const std::vector<uint32_t>&);
        ~vertex_buffer() override;
        void bind() override;
        void unbind() override;

    private:
        uint32_t m_vao;
        uint32_t m_ebo;
        uint32_t m_indices_count;
    };


    class float_buffer : public  ogl::interfaces::vertex_buffer
    {
    public:
        float_buffer(int32_t, std::vector<float>&, std::shared_ptr<ogl::interfaces::vertex_buffer>);
        ~float_buffer() override = default;
        void bind() override;
        void unbind() override;

    private:
        std::shared_ptr<interfaces::vertex_buffer> m_wrappee;
    };
}

