#include "Scene/Core/World.hpp"
#include "Engine.hpp"

World::World(std::string &name) : _name(name)
{}

void World::Init()
{
    _componentManager = std::make_unique<ComponentManager>();
    _entityManager = std::make_unique<EntityManager>();
    _systemManager = std::make_unique<SystemManager>();

    _physicsWorld = Engine::Instance().GetPhysicsManager().createPhysicsWorld();

    //_componentManager->RegisterComponent<Name>();
}