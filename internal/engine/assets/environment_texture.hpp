//
// Created by movleaxedx on 25.11.19.
//


#pragma once

#include <interfaces/texture.hpp>

#include <texture_parameters.hpp>
#include <array>
#include <string>
#include <utility>
#include <cinttypes>
#include <image_format.hpp>

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

        environment_texture(const std::string&, const std::array<std::string, 6>&, const texture_parameters&);
        ~environment_texture() override;
        const std::string& get_name() const override;
        std::pair<int32_t, int32_t> get_size() const override;
        int32_t get_levels() const override;
        const texture_parameters& get_parameters() const override;
        void set_parameters(const texture_parameters& parameters) override;
        void visit(const interfaces::texture_visitor& visitor) const override;
        void set_face(const std::string&, FACE face);
        unsigned char* get_face(FACE face) const;
        image_format get_format() const;

    private:
        std::array<unsigned char*, 6> m_images;
        std::string m_name;
        int32_t m_width = -1;
        int32_t m_height = -1;
        image_format m_format = image_format::undefined;
        texture_parameters m_parameters;
    };

}
