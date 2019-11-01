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

        template<typename T>
        void emplace(const std::string& name, std::shared_ptr<T> resource)
        {
            if (!cached(name)) {
                m_resources.emplace(name, resource);
            }
        }

        template <typename T>
        std::shared_ptr<T> get_resource(const std::string& name) const
        {
            if (cached(name)) {
                return  std::get<std::shared_ptr<T>>(m_resources.at(name));
            }

            return nullptr;
        }

    private:
        gpu_resources m_resources;
    };
} // namespace engine::ogl
