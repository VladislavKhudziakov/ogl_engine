//
// Created by movleaxedx on 15.10.19.
//


#pragma once

#include <interfaces/importer.hpp>
#include <texture2d.hpp>

namespace engine
{
    class texture2d_importer : public interfaces::importer<interfaces::texture>
    {
    public:
        struct import_parameters
        {
            bool mipmapped = false;
            std::string path;
            std::string name;
        };

        explicit texture2d_importer(const import_parameters&);
        ~texture2d_importer() override = default;

        std::shared_ptr<interfaces::texture> import() const override;
        std::string get_name() const override;

    private:
        import_parameters m_parameters;
    };
} // namespace engine
