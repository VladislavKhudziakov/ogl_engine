//
// Created by movleaxedx on 17.10.19.
//


#pragma once

#include <utility>
#include <string>
#include <cinttypes>

#include <texture_parameters.hpp>
#include <interfaces/texture.hpp>
#include <common/image_format.hpp>

namespace engine
{
    class image : public interfaces::texture
    {
    public:
        image(const std::string&, const std::string&, const texture_parameters& = {true});
        ~image() override;
        const std::string& get_name() const override;
        std::pair<int32_t, int32_t> get_size() const override;
        image_format get_format() const;
        const unsigned char* get_data() const;
        int32_t get_levels() const override;
        const texture_parameters& get_parameters() const override;
        void visit(const interfaces::texture_visitor& visitor) const override;
        void set_parameters(const texture_parameters& parameters) override;

    private:
        unsigned char* p_data;
        texture_parameters m_parameters;
        std::string m_name;
        int32_t m_width;
        int32_t m_height;
        image_format m_format;
    };
} // namespace engine
