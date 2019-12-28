//
// Created by movleaxedx on 17.10.19.
//


#pragma once

#include <assets/interfaces/importer.hpp>
#include <assets/shader_program.hpp>
#include <assets/types.hpp>


namespace engine
{
    class shader_importer : public interfaces::importer<shader_program>
    {
    public:
        using shader_data = std::pair<shader_program::shader_type, std::string>;

        shader_importer(const std::string&, const std::initializer_list<shader_data>&);

        assets::shader_program_t import() const override;
        std::string get_name() const override;
        ~shader_importer() override = default;

    private:
        std::string load_file(const std::string&) const;
        std::vector<shader_data> m_data;
        std::string m_program_name;
    };
} // namespace engine
