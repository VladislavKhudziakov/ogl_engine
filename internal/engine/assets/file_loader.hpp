//
// Created by Vladislav Khudiakov on 10/11/19.
//

#pragma once

#include <interfaces/file_loader.hpp>

namespace engine
{
    template<typename T>
    class file_loader : public engine::interfaces::file_loader
    {
    public:
        ~file_loader() override = default;

        T get_file() const
        {
            return m_file;
        }

    protected:
        mutable T m_file;
    };

} // namespace engine