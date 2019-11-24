//
// Created by movleaxedx on 3.11.19.
//


#pragma once

#include <memory>
#include <assets/interfaces/texture_visitor.hpp>

namespace engine::ogl::interfaces
{
    class texture;
}

namespace engine::ogl
{
    class texture_converter : public engine::interfaces::texture_visitor
    {
    public:
        texture_converter() = default;
        ~texture_converter() override = default;

        void accept(const image& image) const override;
        std::unique_ptr<interfaces::texture> get_texture() const;

    private:
        mutable std::unique_ptr<interfaces::texture> m_texture;
    };
}

