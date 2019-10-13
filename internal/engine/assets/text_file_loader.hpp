//
// Created by Vladislav Khudiakov on 10/11/19.
//

#pragma once


#include <file_loader.hpp>
#include <assets/interfaces/file_loader.hpp>
#include <string>



namespace engine
{
    class text_file_loader : public engine::file_loader<std::string>
    {
    public:
        ~text_file_loader() override = default;
        void load(const std::string& file_name) const override;
    };
}
