//
// Created by movleaxedx on 17.10.19.
//


#pragma once

#include <memory>
#include <string>
#include <cinttypes>

#include <interfaces/texture.hpp>

namespace engine
{
    class texture2d : public interfaces::texture
    {
    public:
        explicit texture2d(const std::string&);
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
}

