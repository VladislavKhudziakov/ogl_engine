//
// Created by Vladislav Khudiakov on 10/11/19.
//

#include "perspective.hpp"
engine::perspective::perspective(float znear, float zfar)
    : m_znear(znear)
    , m_zfar(zfar)
{
}


void engine::perspective::set_znear(float znear)
{
    m_znear = znear;
}


void engine::perspective::set_zfar(float zfar)
{
    m_zfar = zfar;
}


float engine::perspective::get_znear() const
{
    return m_znear;
}


float engine::perspective::get_zfar() const
{
    return m_zfar;
}
