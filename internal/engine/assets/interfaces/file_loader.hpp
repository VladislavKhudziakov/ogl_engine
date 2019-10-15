//
// Created by Vladislav Khudiakov on 10/11/19.
//

#pragma once
#include <string>

namespace engine::interfaces
{
    template<typename T>
    class file_loader
    {
    public:
        virtual ~file_loader() = default;
        virtual T load(const std::string& file_name) const = 0;
    };
} // namespace engine::interfaces
