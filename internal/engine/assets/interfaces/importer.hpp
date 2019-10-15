//
// Created by Vladislav Khudiakov on 10/15/19.
//

#pragma once
#include <memory>

namespace engine::interfaces
{
    template<typename T>
    class importer
    {
    public:
        virtual ~importer() = default;
        virtual std::shared_ptr<T> import(const std::string&) const = 0;
    };
} // namespace engine::interfaces
