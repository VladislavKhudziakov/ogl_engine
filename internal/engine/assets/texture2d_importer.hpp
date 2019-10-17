//
// Created by movleaxedx on 15.10.19.
//


#pragma once

#include <interfaces/importer.hpp>
#include <texture_2d.hpp>

namespace engine
{
class texture2d_importer : public interfaces::importer<interfaces::texture>
    {
    public:
        struct import_handler
        {
            virtual ~import_handler() = default;
            void add_next(std::unique_ptr<import_handler>);
            virtual void handle(engine::texture_2d_builder&) const;
        private:
            std::unique_ptr<import_handler> m_next;
        };

        texture2d_importer(const std::string&, const std::string&);
        ~texture2d_importer() override = default;

        std::shared_ptr<interfaces::texture> import() const override;
        std::string get_name() const override;
        texture2d_importer& add_import_handler(std::unique_ptr<import_handler>);
    private:
        std::unique_ptr<import_handler> m_handler;
        std::string m_path;
        std::string m_name;
    };

    struct default_import : texture2d_importer::import_handler
    {
        ~default_import() override = default;
        void handle(engine::texture_2d_builder&) const override;
    };
} // namespace engine
