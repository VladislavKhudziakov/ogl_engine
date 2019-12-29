//
// Created by movleaxedx on 31.10.19.
//


#pragma once

#include <map>
#include <variant>
#include <memory>

//#include <scene/ogl_renderer/shader_program.hpp>
#include <scene/ogl_renderer/shaders/shader_program.hpp>
#include <scene/ogl_renderer/interfaces/texture.hpp>
#include <scene/ogl_renderer/interfaces/vertex_buffer.hpp>


namespace engine
{
    class material;
    class geometry;
    class shader_program;
    class mesh;
    class mesh_bucket;
} // namespace engine

namespace engine::interfaces
{
    class texture;
}

namespace engine::ogl
{
//    class shader_program;

    class gpu_cache
    {
    public:
        using gpu_resource_t = std::variant<
            std::unique_ptr<shader_program>,
            std::unique_ptr<interfaces::texture>,
            std::unique_ptr<interfaces::vertex_buffer>>;


        struct resource_ref
        {
            explicit resource_ref(gpu_resource_t res)
                : resource(std::move(res))
            {
                ++refs_counter;
            }

            ~resource_ref() = default;

            uint64_t refs_counter = 0;
            engine::ogl::gpu_cache::gpu_resource_t resource;
        };

        using gpu_resources_t = std::map<std::string, resource_ref>;

        gpu_cache() = default;
        gpu_cache(const gpu_cache&) = delete;
        gpu_cache(gpu_cache&&) = default;
        const gpu_cache& operator=(const gpu_cache&) = delete;
        gpu_cache& operator=(gpu_cache&&) = default;
        ~gpu_cache() = default;

        template<typename T>
        const std::unique_ptr<T>& get_resource(const std::string& name) const
        {
            const auto it = m_res.find(name);

            if (it == m_res.end()) {
                throw std::runtime_error("ERROR: resource with name " + name + " does not exist");
            }

            auto&& [res_name, ref] = *it;

            return std::get<std::unique_ptr<T>>(ref.resource);
        }

        void acquire_geometry(const engine::geometry&);
        void release_geometry(const engine::geometry&);
        void acquire_shader(const engine::shader_program&);
        void release_shader(const engine::shader_program&);
        void acquire_texture(const engine::interfaces::texture&);
        void release_texture(const engine::interfaces::texture&);
        void acquire_material(const engine::material&);
        void release_material(const engine::material&);
        void acquire_mesh(const engine::mesh&);
        void release_mesh(const engine::mesh&);
        void acquire_mesh_data(const engine::mesh_bucket&);
        void release_mesh_data(const engine::mesh_bucket&);

    private:
        gpu_resources_t m_res;
    };
} // namespace engine::ogl
