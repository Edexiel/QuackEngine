//
// Created by g.nisi on 2/23/21.
//
#ifndef QUACKENGINE_COMPONENT_HPP
#define QUACKENGINE_COMPONENT_HPP

#include "Scene/Entity.hpp"

enum class Type
{
    E_STATIC,
    E_DYNAMIC
};

class Component
{
    virtual void update() = 0;
};

#endif // QUACKENGINE_COMPONENT_HPP
