//
// Created by Vladislav Khudiakov on 10/15/19.
//

#pragma once
#include <string>
#include <variant>
#include <vector>
#include <map>

#include <mesh_importer.hpp>
#include <interfaces/texture.hpp>
#include <interfaces/importer.hpp>
#include <shader_program.hpp>
#include <texture.hpp>
#include <material.hpp>

namespace engine
{
    class assets_manager
    {
    public:
        using assets = std::map<std::string, std::variant<
            std::shared_ptr<mesh_data>
            , std::shared_ptr<material>
            , std::shared_ptr<interfaces::texture>
            , std::shared_ptr<shader_program>>>;

        assets_manager();
        ~assets_manager() = default;

        template<typename T>
        engine::assets_manager& import(const interfaces::importer<T>& importer)
        {
            if (m_storage.find(importer.get_name()) == m_storage.end()) {
                m_storage.emplace(importer.get_name(), importer.import());
            } else {
                throw std::logic_error("ERROR: INSTANCE WITH GIVEN NAME ALREADY EXIST");
            }

            return *this;
        }

        
        template<typename T>
        engine::assets_manager& add(std::shared_ptr<T> instance, const std::string& name)
        {
            if (m_storage.find(name) == m_storage.end()) {
                m_storage.emplace(name, instance);
            } else {
                throw std::logic_error("ERROR: INSTANCE WITH GIVEN NAME ALREADY EXIST");
            }
            return *this;
        }


        template<typename T>
        std::shared_ptr<T> get(const std::string& name)
        {
            try {
                return std::get<std::shared_ptr<T>>(m_storage.at(name));
            } catch (...) {
                return nullptr;
            }
        }

    private:
        assets m_storage;
    };
} // namespace engine
