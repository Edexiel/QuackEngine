//
// Created by g.nisi on 2/23/21.
//

#ifndef QUACKENGINE_SCENE_HPP
#define QUACKENGINE_SCENE_HPP

#include "Scene/Entity/Entity.hpp"

class Scene
{
public:
    void update(float DeltaTime);
    void fixedUpdate(float FixedDeltaTime);
    void draw();
    void load();
};

#endif // QUACKENGINE_SCENE_HPP
