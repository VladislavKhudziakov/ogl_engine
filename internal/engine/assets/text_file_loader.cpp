//
// Created by Vladislav Khudiakov on 10/11/19.
//

#include <fstream>
#include <text_file_loader.hpp>


std::string engine::text_file_loader::load(const std::string& file_name) const
{
    std::string file;
    std::ifstream fin;
    fin.open(file_name);
    std::getline(fin, file, '\0');
    fin.close();
    return file;
}
