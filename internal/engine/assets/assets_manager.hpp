//
// Created by Vladislav Khudiakov on 10/15/19.
//

#pragma once

#include <assets/mesh_importer.hpp>
#include <assets/interfaces/texture.hpp>
#include <assets/interfaces/importer.hpp>
#include <assets/texture_parameters.hpp>
#include <assets/types.hpp>

#include <common/image_format.hpp>
#include <common/vertex.hpp>

#include <functional>
#include <string>
#include <variant>
#include <vector>
#include <map>

namespace engine
{
    class assets_manager
    {
    public:
        using assets_t = std::map<
            std::string,
            std::variant<
                std::shared_ptr<mesh_bucket>,
                std::shared_ptr<material>,
                std::shared_ptr<interfaces::texture>,
                std::shared_ptr<shader_program>>>;

        assets_manager();
        ~assets_manager() = default;

        static assets::image_t make_image(uint8_t*, int32_t, int32_t, image_format, const std::function<void(uint8_t*)>&);
        static assets::texture2d_t make_texture2d(const std::string&, image, const texture_parameters& parameters = texture_parameters());
        static assets::env_texture_t make_env_texture(const std::string&, std::vector<image>, const texture_parameters&);

        static assets::mesh_bucket_t make_mesh_bucket();

        static assets::mesh_t make_mesh(const std::string&, assets::geometry_t geometry, const engine::assets::material_t& = nullptr);
        static assets::mesh_t make_mesh();

        static assets::geometry_t make_geometry(const std::string&, std::vector<vertex>&&, std::vector<face>&&);
        static assets::geometry_t make_geometry(const std::string&, std::vector<vertex>&, std::vector<face>&);

        template<typename... Args>
        static std::shared_ptr<material> make_material(Args&&... args)
        {
            return std::make_shared<material>(std::forward<Args>(args)...);
        }


        template<typename T>
        engine::assets_manager& import(const interfaces::importer<T>& importer)
        {
            if (m_storage.find(importer.get_name()) == m_storage.end()) {
                m_storage.emplace(importer.get_name(), importer.import());
            } else {
                throw std::logic_error("ERROR: INSTANCE WITH GIVEN NAME ALREADY EXIST");
            }

            return *this;
        }


        template<typename T>
        engine::assets_manager& add(std::shared_ptr<T> instance, const std::string& name)
        {
            if (m_storage.find(name) == m_storage.end()) {
                m_storage.emplace(name, instance);
            } else {
                throw std::logic_error("ERROR: INSTANCE WITH GIVEN NAME ALREADY EXIST");
            }
            return *this;
        }


        template<typename T>
        std::shared_ptr<T> get(const std::string& name)
        {
            try {
                return std::get<std::shared_ptr<T>>(m_storage.at(name));
            } catch (...) {
                return nullptr;
            }
        }

        void release_resource(const std::string&);

    private:
        assets_t m_storage;
    };
} // namespace engine
