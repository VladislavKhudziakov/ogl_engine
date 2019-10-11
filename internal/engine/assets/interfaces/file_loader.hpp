//
// Created by Vladislav Khudiakov on 10/11/19.
//

#pragma once
#include <string>

namespace engine::interfaces
{
    class file_loader
    {
    public:
        virtual ~file_loader() = default;
        virtual void load(const std::string& file_name) = 0;
    };
} // namespace engine::interfaces
