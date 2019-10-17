//
// Created by movleaxedx on 17.10.19.
//

#include <fstream>
#include <shader_importer.hpp>

engine::shader_importer::shader_importer(
    const std::string& vshader_path,
    const std::string& fshader_path,
    const std::string& name)
    : m_vshader_path(vshader_path)
    , m_fshader_path(fshader_path)
    , m_program_name(name)
{
}


std::shared_ptr<engine::shader_program> engine::shader_importer::import() const
{
    auto vshader_source = load_file(m_vshader_path);
    auto fshader_source = load_file((m_fshader_path));
    return std::make_shared<shader_program>(vshader_source, fshader_source);
}


std::string engine::shader_importer::get_name() const
{
    return m_program_name;
}


std::string engine::shader_importer::load_file(const std::string& file_path) const
{
    std::string output_file;

    std::string file;
    std::ifstream fin;
    fin.open(file_path);
    std::getline(fin, file, '\0');
    fin.close();

    return output_file;
}
