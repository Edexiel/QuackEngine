#ifndef QUACKENGINE_CAMERAGAMEPLAYSYSTEM_HPP
#define QUACKENGINE_CAMERAGAMEPLAYSYSTEM_HPP

#include "Scene/Core/System.hpp"

class CameraGameplaySystem : public System
{
private:
    static void SearchPlayer(Entity id);
    static void LookAtEntity(Entity id);
public:
    CameraGameplaySystem();
    void Update();
};

#endif //QUACKENGINE_CAMERAGAMEPLAYSYSTEM_HPP