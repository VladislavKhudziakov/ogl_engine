//
// Created by movleaxedx on 17.10.19.
//


#pragma once

#include <assets/texture_parameters.hpp>
#include <assets/interfaces/texture.hpp>
#include <assets/image.hpp>
#include <common/image_format.hpp>

#include <utility>
#include <string>
#include <cinttypes>


namespace engine
{
    class image_2d_texture : public interfaces::texture
    {
    public:
        image_2d_texture(const std::string&, image, const texture_parameters& = {true});
        ~image_2d_texture() override = default;
        const std::string& get_name() const override;
        std::pair<int32_t, int32_t> get_size() const override;
        image_format get_format() const;
        const image& get_image() const;
        int32_t get_levels() const override;
        const texture_parameters& get_parameters() const override;
        void visit(const interfaces::texture_visitor& visitor) const override;
        void set_parameters(const texture_parameters& parameters) override;

    private:
        image m_image;
        texture_parameters m_parameters;
        std::string m_name;
    };
} // namespace engine
