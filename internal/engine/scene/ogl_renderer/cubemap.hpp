//
// Created by movleaxedx on 25.11.19.
//


#pragma once
#include <common/image_format.hpp>
#include <scene/ogl_renderer/interfaces/texture.hpp>

#include <memory>
#include <array>

namespace engine
{
    class environment_texture;
}

//todo make base class
namespace engine::ogl
{
    class cubemap : public interfaces::texture
    {
    public:
        struct cubemap_data {
            int32_t width;
            int32_t height;
            image_format format;
            std::array<unsigned char*, 6> data;
        };

        static std::unique_ptr<cubemap> from_env_texture(const environment_texture&);
        explicit cubemap(const cubemap_data&);
        cubemap(const cubemap&) = delete;
        cubemap(cubemap&&) = default;
        const cubemap& operator=(const cubemap&) = delete;
        cubemap& operator=(cubemap&&) = default;
        ~cubemap() override;
        void bind(int i) override;
        void unbind() override;

    private:
        uint32_t m_name = 0;
        int32_t m_curr_slot = -1;
    };
}

