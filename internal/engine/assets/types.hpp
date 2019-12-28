//
// Created by movleaxedx on 28.12.19.
//


#pragma once
#include <memory>

namespace engine
{
    class image;
    class image_2d_texture;
    class environment_texture;

    class mesh_bucket;
    class mesh;
    class geometry;

    class material;

    class shader_program;
}

namespace engine::interfaces
{
    class texture;
}

namespace engine::assets
{
    using image_t = std::shared_ptr<image>;
    using texture2d_t = std::shared_ptr<image_2d_texture>;
    using env_texture_t = std::shared_ptr<environment_texture>;
    using texture_t = std::shared_ptr<interfaces::texture>;

    using mesh_bucket_t = std::shared_ptr<mesh_bucket>;
    using mesh_t = std::unique_ptr<mesh>;
    using geometry_t = std::unique_ptr<geometry>;

    using material_t = std::shared_ptr<material>;

    using shader_program_t = std::shared_ptr<shader_program>;
}
