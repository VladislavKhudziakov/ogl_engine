//
// Created by movleaxedx on 23.11.19.
//


#pragma once

namespace engine
{
    struct material_config;

    class material_config_resolver
    {
    public:
        explicit material_config_resolver(const material_config&);
        ~material_config_resolver() = default;
        void set_config();

    private:
        const material_config& m_config_ref;
        void set_blending();
        void set_culling();
    };
} // namespace engine
