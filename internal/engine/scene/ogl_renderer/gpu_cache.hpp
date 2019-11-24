//
// Created by movleaxedx on 31.10.19.
//


#pragma once

#include <map>
#include <variant>
#include <memory>

#include <scene/ogl_renderer/shader_program.hpp>
#include <scene/ogl_renderer/interfaces/texture.hpp>
#include <scene/ogl_renderer/interfaces/vertex_buffer.hpp>


namespace engine
{
    class material;
    class geometry;
    class shader_program;
    class mesh;
    class mesh_data;
} // namespace engine

namespace engine::interfaces
{
    class texture;
}

namespace engine::ogl
{
    class gpu_cache
    {
    public:
        using gpu_resources = std::variant<
            std::unique_ptr<shader_program>,
            std::unique_ptr<interfaces::texture>,
            std::unique_ptr<interfaces::vertex_buffer>>;

        using gpu_resources_map = std::map<std::string, gpu_resources>;

        struct resource_ref
        {
            resource_ref()
            {
                ++refs_counter;
            }

            ~resource_ref() = default;

            uint64_t refs_counter = 0;
            engine::ogl::gpu_cache::gpu_resources resource;
        };

        gpu_cache() = default;
        ~gpu_cache() = default;

        bool cached(const std::string& name) const;

        template<typename T>
        const std::unique_ptr<T>& get_resource(const std::string& name) const
        {
            if (cached(name)) {
                return std::get<std::unique_ptr<T>>(m_resources.at(name));
            }

            throw std::runtime_error("ERROR: resourse with name " + name + "does not exist");
        }

        void cache_material(const engine::material&);
        void cache_shader(const engine::shader_program&);
        void cache_texture(const engine::interfaces::texture&);
        void cache_geometry(const engine::geometry&);
        void cache_mesh(const engine::mesh&);
        void cache_mesh_data(const engine::mesh_data&);


    private:
        template<typename T>
        void emplace(const std::string& name, std::unique_ptr<T> resource)
        {
            if (!cached(name)) {
                m_resources.emplace(name, std::move(resource));
            }
        }

        gpu_resources_map m_resources;
        std::map<std::string, resource_ref> m_res;
    };
} // namespace engine::ogl
