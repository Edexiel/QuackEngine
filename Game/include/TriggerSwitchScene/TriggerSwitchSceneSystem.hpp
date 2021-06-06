#ifndef QUACKENGINE_TRIGGERSWITCHSCENESYSTEM_HPP
#define QUACKENGINE_TRIGGERSWITCHSCENESYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Engine.hpp"

class TriggerSwitchSceneSystem : public System
{
public:
    void Init();
private:
    void SwitchScene(Entity entity1, Entity entity2);

};

#endif //QUACKENGINE_TRIGGERSWITCHSCENESYSTEM_HPP