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
}

namespace engine::interfaces
{
    class texture;
}

namespace engine::ogl
{
    class gpu_cache
    {
    public:
        using gpu_resources = std::map<
            std::string,
            std::variant<
                std::shared_ptr<shader_program>,
                std::shared_ptr<interfaces::texture>,
                std::shared_ptr<interfaces::vertex_buffer>>>;

        gpu_cache() = default;
        ~gpu_cache() = default;

        bool cached(const std::string& name) const;

        template <typename T>
        std::shared_ptr<T> get_resource(const std::string& name) const
        {
            if (cached(name)) {
                return  std::get<std::shared_ptr<T>>(m_resources.at(name));
            }

            return nullptr;
        }

        void cache_material(const engine::material&);
        void cache_shader(const engine::shader_program&);
        void cache_texture(const engine::interfaces::texture&);
        void cache_geometry(const engine::geometry&);
        void cache_mesh(const engine::mesh&);
        void cache_mesh_data(const engine::mesh_data&);


    private:
        template<typename T>
        void emplace(const std::string& name, std::shared_ptr<T> resource)
        {
            if (!cached(name)) {
                m_resources.emplace(name, resource);
            }
        }

        gpu_resources m_resources;
    };
} // namespace engine::ogl
