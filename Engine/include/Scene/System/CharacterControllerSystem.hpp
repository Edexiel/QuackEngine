#ifndef QUACKENGINE_CHARACTERCONTROLLERSYSTEM_HPP
#define QUACKENGINE_CHARACTERCONTROLLERSYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Scene/Core/Types.hpp"

class CharacterControllerSystem: public System
{
public:
    static bool RaycastTest(Entity id);
};

#endif //QUACKENGINE_CHARACTERCONTROLLERSYSTEM_HPP
