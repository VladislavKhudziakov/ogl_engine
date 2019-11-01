//
// Created by Vladislav Khudiakov on 10/8/19.
//

#pragma once
#include <cstdint>
#include <vector>
#include <memory>

#include <common/vectors.hpp>
#include <interfaces/geometry_buffer.hpp>


//TODO: exception in destructor
namespace engine
{
    class geometry : public interfaces::geometry_buffer
    {
    public:
        struct vertex
        {
            vertex(float x, float y, float z, float u, float v, float n_x, float n_y, float n_z)
                : position{x, y, z}
                , uv{u, v}
                , normal{n_x, n_y, n_z}
            {
            }

            vec3 position;
            vec2 uv;
            vec3 normal;
        };

        geometry(const std::vector<engine::geometry::vertex>&, const ::std::vector<int>&);
        ~geometry() override;

        void draw() const override;
        void bind() override;
        void unbind() override;

    private:
        uint32_t m_vao;
        uint32_t m_ebo;
        uint32_t m_indices_count;
    };

    class float_buffer : public interfaces::geometry_buffer
    {
    public:
        float_buffer(int32_t, std::vector<float>&, std::shared_ptr<interfaces::geometry_buffer>);
        ~float_buffer() override = default;
        void bind() override;
        void unbind() override;
        void draw() const override;

    private:
        std::shared_ptr<interfaces::geometry_buffer> m_wrappee;
    };
} // namespace engine
