//
// Created by movleaxedx on 14.10.19.
//


#pragma once

#include <interfaces/texture.hpp>
#include <memory>
#include <cstdint>

namespace engine
{
    class texture_2d : public engine::interfaces::texture
    {
        friend class texture_2d_builder;

    public:
        ~texture_2d() override;
        void bind(int32_t) override;
        void unbind() override;

    private:
        texture_2d() = default;
        uint32_t m_texture_name = 0;
        int32_t m_curr_slot = -1;
    };


    class texture_2d_builder
    {
    public:
        //TODO: protection from fool
        struct build_command_base
        {
            virtual ~build_command_base() = default;
            virtual void execute() const = 0;
        };

        texture_2d_builder();
        ~texture_2d_builder() = default;
        texture_2d_builder& from_file(const std::string&);
        texture_2d_builder& apply_command(const build_command_base&);
        std::shared_ptr<texture_2d> generate_default_from_file(const std::string&);
        std::shared_ptr<texture_2d> generate_texture();

    private:
        std::shared_ptr<texture_2d> m_texture;
    };


    struct generate_mipmap : texture_2d_builder::build_command_base
    {
        ~generate_mipmap() override = default;
        void execute() const override;
    };


    struct set_filtration : texture_2d_builder::build_command_base
    {
        enum class filtration_type
        {
            linear,
            nearest
        } type;

        explicit set_filtration(filtration_type);
        ~set_filtration() override = default;
        void execute() const override;
    };
} // namespace engine
