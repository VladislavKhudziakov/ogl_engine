//
// Created by Vladislav Khudiakov on 10/15/19.
//

#pragma once
#include <memory>
#include <string>

namespace engine::interfaces
{
    template<typename T>
    class importer
    {
    public:
        virtual ~importer() = default;
        virtual std::shared_ptr<T> import() const = 0;
        virtual std::string get_name() const = 0;
    };
} // namespace engine::interfaces
