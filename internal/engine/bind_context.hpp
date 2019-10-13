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
        explicit bind_context(T& target)
            : m_context_target(target)
        {
            target.bind();
        }


        ~bind_context()
        {
            m_context_target.unbind();
        }

    private:
        T& m_context_target;
    };
} // namespace engine
