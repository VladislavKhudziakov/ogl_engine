//
// Created by movleaxedx on 31.10.19.
//

#include <scene/ogl_renderer/scene_cache.hpp>


bool engine::ogl::scene_cache::cached(const std::string& name) const
{
    return m_resources.find(name) != m_resources.end();
}
