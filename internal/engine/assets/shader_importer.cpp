//
// Created by movleaxedx on 17.10.19.
//

#include <fstream>
#include <assets/shader_importer.hpp>
#include <assets/assets_manager.hpp>

engine::shader_importer::shader_importer(
    const std::string& name,
    const std::initializer_list<shader_data>& data)
    : m_data{data}
    , m_program_name{name}
{
}


std::shared_ptr<engine::shader_program> engine::shader_importer::import() const
{
    std::vector<shader_program::shader> shaders;
    for (const auto& [type, path] : m_data) {
        shaders.emplace_back();
        shaders.back().type = type;
        shaders.back().source = load_file(path);
    }


    return assets_manager::make_shader_program(m_program_name, shaders);
}


std::string engine::shader_importer::get_name() const
{
    return m_program_name;
}


std::string engine::shader_importer::load_file(const std::string& file_path) const
{
    std::string output_file;

    std::ifstream fin;
    fin.open(file_path);
    std::getline(fin, output_file, '\0');
    fin.close();

    return output_file;
}
