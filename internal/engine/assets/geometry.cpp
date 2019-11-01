//
// Created by Vladislav Khudiakov on 10/8/19.
//

#include <geometry.hpp>


engine::geometry::geometry(const std::string& name, std::vector<vertex>& vertices, std::vector<face>& faces)
    : m_name(name)
    , m_vertices(std::move(vertices))
    , m_faces(std::move(faces))
{
}


engine::geometry::geometry(const std::string& name, std::vector<vertex>&& vertices, std::vector<face>&& faces)
    : m_name(name)
    , m_vertices(std::move(vertices))
    , m_faces(std::move(faces))
{
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
