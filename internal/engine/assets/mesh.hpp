//
// Created by movleaxedx on 13.10.19.
//


#pragma once
#include <memory>
#include <string>

#include <glm/mat4x4.hpp>
#include <types.hpp>

namespace engine
{
    class material;

    class mesh
    {
    public:
        mesh() = default;
        ~mesh();

        explicit mesh(const std::string&, assets::geometry_t geometry, const assets::material_t& material = nullptr);

        const assets::geometry_t& get_geometry() const;
        assets::geometry_t& get_geometry();

        void set_geometry(assets::geometry_t);
        void attach_material(const assets::material_t&);
        std::shared_ptr<material> get_material() const;
        bool has_material() const;

        const std::string& get_name() const;

    private:
        assets::geometry_t m_geometry;
        assets::material_t m_material;
        std::string m_name;
    };
} // namespace engine
