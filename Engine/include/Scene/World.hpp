//
// Created by g.nisi on 2/23/21.
//

#ifndef QUACKENGINE_WORLD_HPP
#define QUACKENGINE_WORLD_HPP

#include "Scene/Core/Ecs.hpp"
#

class World
{
private:
    Ecs _world;
public:
    void Init();
    void Update(float deltaTime);
    void Clear();
};

#endif // QUACKENGINE_WORLD_HPP
