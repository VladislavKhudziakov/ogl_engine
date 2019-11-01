//
// Created by movleaxedx on 15.10.19.
//


#pragma once

#include <interfaces/importer.hpp>
#include <image.hpp>

namespace engine
{
    class image_importer : public interfaces::importer<engine::interfaces::texture>
    {
    public:
        struct import_parameters
        {
            std::string path;
            std::string name;
        };

        explicit image_importer(const import_parameters&);
        ~image_importer() override = default;

        std::shared_ptr<engine::interfaces::texture> import() const override;
        std::string get_name() const override;

    private:
        import_parameters m_parameters;
    };
} // namespace engine
