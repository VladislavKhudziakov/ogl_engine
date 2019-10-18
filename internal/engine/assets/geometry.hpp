//
// Created by Vladislav Khudiakov on 10/8/19.
//

#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <interfaces/geometry_buffer.hpp>


//TODO: exception in destructor
namespace engine
{
    class geometry : public interfaces::geometry_buffer
    {
    public:
        struct vertex
        {
            float position[3];
            float uv[2];
            float normal[3];
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
        bool is_bounded = false;
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
