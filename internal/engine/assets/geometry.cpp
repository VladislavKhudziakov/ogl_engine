//
// Created by Vladislav Khudiakov on 10/8/19.
//

#include <geometry.hpp>


engine::geometry::geometry(const std::string& name, std::vector<vertex>& vertices, std::vector<face>& faces)
    : m_name(name)
    , m_vertices(std::move(vertices))
    , m_faces(std::move(faces))
{
    count_vertices();
}


engine::geometry::geometry(const std::string& name, std::vector<vertex>&& vertices, std::vector<face>&& faces)
    : m_name(name)
    , m_vertices(std::move(vertices))
    , m_faces(std::move(faces))
{
    count_vertices();
}


const std::string& engine::geometry::get_name() const
{
    return m_name;
}


const std::vector<engine::vertex>& engine::geometry::get_vertices() const
{
    return m_vertices;
}


const std::vector<engine::face>& engine::geometry::get_faces() const
{
    return m_faces;
}

uint32_t engine::geometry::get_vertices_count() const
{
    return m_vertices_count;
}

void engine::geometry::count_vertices()
{
    m_vertices_count = 0;

    for (const auto& face : m_faces) {
        m_vertices_count += face.indices.size();
    }
}
