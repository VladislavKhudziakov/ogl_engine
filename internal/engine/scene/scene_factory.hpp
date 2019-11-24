//
// Created by movleaxedx on 24.11.19.
//


#pragma once

#include <memory>

namespace engine
{
    class scene;
    class scene_object;

    class scene_factory
    {
    public:
        explicit scene_factory(scene&);
        ~scene_factory() = default;
        std::shared_ptr<scene_object> make_scene_object(const std::string&);

    private:
        scene& m_scene_ref;
    };
}

