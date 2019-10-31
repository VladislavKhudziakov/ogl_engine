//
// Created by movleaxedx on 31.10.19.
//


#pragma once

#include <map>
#include <variant>
#include <memory>

#include <scene/ogl_renderer/shader_program.hpp>


namespace engine::ogl
{
    class scene_cache
    {
    public:
        using gpu_resources = std::map<std::string, std::variant<std::shared_ptr<shader_program>>>;

        scene_cache() = default;
        ~scene_cache() = default;

        bool cached(const std::string& name) const;

        template<typename T, typename... Args>
        void emplace(const std::string& name, Args&& ...args)
        {
            if (!cached(name)) {
                auto resource = std::make_shared<T>(std::forward(args...));
                m_resources.emplace(resource);
            }
        }

    private:
        gpu_resources m_resources;
    };
} // namespace engine::ogl
