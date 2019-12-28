//
// Created by Vladislav Khudiakov on 10/8/19.
//

#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include <common/vectors.hpp>
#include <common/vertex.hpp>
#include <interfaces/geometry_buffer.hpp>


namespace engine
{
    class geometry
    {
    public:
        geometry(const std::string&, std::vector<vertex>&, std::vector<face>&);
        geometry(const std::string&, std::vector<vertex>&&, std::vector<face>&&);
        ~geometry() = default;

        const std::string& get_name() const;
        const std::vector<vertex>& get_vertices() const;
        const std::vector<face>& get_faces() const;

    private:
        std::string m_name;
        std::vector<vertex> m_vertices;
        std::vector<face> m_faces;
    };
} // namespace engine
