//
// Created by movleaxedx on 14.10.19.
//


#pragma once

namespace engine
{
    struct texture_parameters;
}

namespace engine::interfaces
{
    class texture_visitor;

    class texture
    {
    public:
        virtual ~texture() = default;
        virtual const std::string& get_name() const = 0;
        virtual std::pair<int32_t, int32_t> get_size() const = 0;
        virtual int32_t get_levels() const = 0;
        virtual const texture_parameters& get_parameters() const = 0;
        virtual void set_parameters(const texture_parameters&) = 0;
        virtual void visit(const texture_visitor&) const = 0;
    };
} // namespace engine::interfaces
