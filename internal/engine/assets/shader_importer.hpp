//
// Created by movleaxedx on 17.10.19.
//


#pragma once

#include <interfaces/importer.hpp>
#include <shader_program.hpp>


namespace engine
{
    class shader_importer : public interfaces::importer<shader_program>
    {
    public:
        shader_importer(const std::string&, const std::string&, const std::string&);

        std::shared_ptr<shader_program> import() const override;
        std::string get_name() const override;
        ~shader_importer() override = default;
    private:
        std::string load_file(const std::string&) const;
        std::string m_vshader_path;
        std::string m_fshader_path;
        std::string m_program_name;
    };
}

