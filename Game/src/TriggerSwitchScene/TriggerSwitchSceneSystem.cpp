#include "TriggerSwitchScene/TriggerSwitchSceneSystem.hpp"
#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/Core/World.hpp"
#include "Engine.hpp"

#include "Player/PlayerComponent.hpp"
#include "TriggerSwitchScene/TriggerSwitchSceneComponent.hpp"

using namespace Component;

void TriggerSwitchSceneSystem::SwitchScene(Entity entity1, Entity entity2)
{
    auto &engine = Engine::Instance();
    auto &world = engine.GetCurrentWorld();
    if(world.HasComponent<TriggerSwitchSceneComponent>(entity1) && world.HasComponent<PlayerComponent>(entity2))
    {
        auto &triggerSwitchSceneComponent = world.GetComponent<TriggerSwitchSceneComponent>(entity1);
        world.GetSystem<PhysicsSystem>()->SetIsSwitchingScene(true);
        world.GetSystem<PhysicsSystem>()->SetWorldName(triggerSwitchSceneComponent.world);

    }
}

void TriggerSwitchSceneSystem::Init()
{
    auto &world = Engine::Instance().GetCurrentWorld();
    for (Entity entity: _entities)
    {
        auto &rigidBody = world.GetComponent<RigidBody>(entity);
        PhysicsSystem::SetPhysicEvent(entity, PhysicsEventType::OverlapStart, this, &TriggerSwitchSceneSystem::SwitchScene);
    }
}