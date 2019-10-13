//
// Created by Vladislav Khudiakov on 10/8/19.
//

#pragma once
#include <cstdint>
#include <vector>
#include <memory>


//TODO: exception in destructor
namespace engine
{
    class geometry
    {
        friend class geometry_builder;

    public:
        struct vertex
        {
            float position[3];
            float uv[2];
            float normal[3];
        };

        ~geometry();

        void draw() const;
        void bind();
        void unbind();

    private:
        geometry();
        uint32_t vao;
        uint32_t ebo;
        uint32_t indices_count;
        bool is_bounded = false;
    };


    class geometry_builder
    {
        //TODO give rename methods/reconsider creating of vao
    public:
        struct add_buffer_command_base
        {
            friend geometry_builder;

            ~add_buffer_command_base() = default;
            virtual void execute() const = 0;

        protected:
            mutable uint32_t buffer;
        };

        geometry_builder();
        ~geometry_builder() = default;

        geometry_builder& create_default(
            const std::vector<geometry::vertex>&, const ::std::vector<int>&);

        std::shared_ptr<geometry> generate_mesh();

        std::shared_ptr<geometry> generate_default_mesh(
            const std::vector<geometry::vertex>&, const ::std::vector<int>&);

        geometry_builder& append_buffer(const add_buffer_command_base&);

    private:
        std::shared_ptr<geometry> m_geometry;
        std::vector<uint32_t> vbo_list;
    };


    struct append_float_buffer : geometry_builder::add_buffer_command_base
    {
        std::vector<float> data;
        uint32_t shader_location;
        void execute() const override;
    };
} // namespace engine
