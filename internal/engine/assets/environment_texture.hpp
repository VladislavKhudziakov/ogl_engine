//
// Created by movleaxedx on 25.11.19.
//


#pragma once

#include <interfaces/texture.hpp>
#include <assets/image.hpp>
#include <texture_parameters.hpp>

#include <array>
#include <string>
#include <utility>
#include <cinttypes>

namespace engine
{
    //todo make base class
    class environment_texture : public interfaces::texture
    {
    public:
        enum class FACE
        {
            RIGHT, LEFT, TOP, BOTTOM, BACK, FRONT
        };

        environment_texture(const std::string&, std::vector<image>, const texture_parameters&);
        ~environment_texture() override = default;
        const std::string& get_name() const override;
        std::pair<int32_t, int32_t> get_size() const override;
        int32_t get_levels() const override;
        const texture_parameters& get_parameters() const override;
        void set_parameters(const texture_parameters& parameters) override;
        void visit(const interfaces::texture_visitor& visitor) const override;
        void set_face(image, FACE face);
        const image& get_face(FACE face) const;
        image_format get_format() const;

    private:
        std::vector<image> m_images;
        std::string m_name;
        texture_parameters m_parameters;
    };

}
