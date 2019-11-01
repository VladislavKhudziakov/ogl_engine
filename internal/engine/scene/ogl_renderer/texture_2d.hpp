
//
// Created by movleaxedx on 17.10.19.
//


#pragma once

#include <memory>
#include <string>
#include <cinttypes>


#include <common/image_format.hpp>
#include <scene/ogl_renderer/interfaces/texture.hpp>


namespace engine
{
    class image;
}

namespace engine::ogl
{
    class texture2d : public ogl::interfaces::texture
    {
    public:
        struct image_data {
            int32_t width;
            int32_t height;
            image_format format;
            const unsigned char* data;
        };

        static std::shared_ptr<texture2d> from_image(const engine::image&);
        explicit texture2d(const image_data&);
        void bind(int) override;
        void unbind() override;
        ~texture2d() override;

    private:
        uint32_t m_name;
        int32_t m_curr_slot = -1;
    };


    class mipmapped : public interfaces::texture
    {
    public:
        explicit mipmapped(std::shared_ptr<interfaces::texture>);
        ~mipmapped() override = default;
        void bind(int) override;
        void unbind() override;

    private:
        std::shared_ptr<interfaces::texture> m_wrappee;
    };
} // namespace engine::ogl

