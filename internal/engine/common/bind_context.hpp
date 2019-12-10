//
// Created by movleaxedx on 13.10.19.
//


#pragma once

//TODO: remove reference?
//TODO: make mono behaviour?
namespace engine
{
    template<typename T>
    class bind_context
    {
    public:
        template<typename... Args>
        explicit bind_context(T& target, Args... args)
            : m_context_target(target)
        {
            target.bind(args...);
        }


        ~bind_context()
        {
            m_context_target.unbind();
        }

    private:
        T& m_context_target;
    };
} // namespace engine
