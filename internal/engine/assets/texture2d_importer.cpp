//
// Created by movleaxedx on 15.10.19.
//

#include "texture2d_importer.hpp"

void engine::texture2d_importer::import_handler::add_next(std::unique_ptr<import_handler> handler)
{
    if (m_next != nullptr) {
        m_next->add_next(std::move(handler));
        return;
    }

    m_next = std::move(handler);
}


void engine::texture2d_importer::import_handler::handle(engine::texture_2d_builder& builder) const
{
    if (m_next) {
        m_next->handle(builder);
    }
}


std::shared_ptr<engine::interfaces::texture> engine::texture2d_importer::import() const
{
    texture_2d_builder builder;
    builder.from_file(m_path);
    m_handler->handle(builder);
    return builder.generate_texture();
}


std::string engine::texture2d_importer::get_name() const
{
    return m_name;
}


engine::texture2d_importer& engine::texture2d_importer::add_import_handler(std::unique_ptr<import_handler> handler)
{
    m_handler->add_next(std::move(handler));
    return *this;
}
engine::texture2d_importer::texture2d_importer(const std::string& file_path, const std::string& name)
    : m_path(file_path)
    , m_name(name)
{
}


void engine::default_import::handle(engine::texture_2d_builder& builder) const
{
    builder.apply_command(generate_mipmap());
    builder.apply_command(set_filtration{set_filtration::filtration_type::nearest});
    ;
}
