//
// Created by Vladislav Khudiakov on 10/11/19.
//

#pragma once

namespace engine
{
    class perspective
    {
    public:
        perspective(float m_znear, float m_zfar);

        void set_znear(float);
        void set_zfar(float);

        float get_znear() const;
        float get_zfar() const;

    private:
        float m_znear;
        float m_zfar;
    };
} // namespace engine
