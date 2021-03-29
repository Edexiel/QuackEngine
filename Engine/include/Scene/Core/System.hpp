//
// Created by gnisi on 22/03/2021.
//

#ifndef QUACKENGINE_SYSTEM_HPP
#define QUACKENGINE_SYSTEM_HPP

#include <set>

#include "Types.hpp"

class System
{
protected:
    //World& _ecs;
public:
    std::set<Entity> _entities;

    explicit System()
    {}
};

#endif //QUACKENGINE_SYSTEM_HPP
