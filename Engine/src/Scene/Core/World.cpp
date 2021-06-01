#include "Scene/Core/World.hpp"
#include "Engine.hpp"

World::World(std::string &name) : _name(name)
{}

void World::Init(Engine &engine)
{
    _componentManager = std::make_unique<ComponentManager>();
    _entityManager = std::make_unique<EntityManager>();
    _systemManager = std::make_unique<SystemManager>();
    _physicsWorld = engine.GetPhysicsManager().createPhysicsWorld();
    _physicsWorld->setEventListener(&engine.GetPhysicsEventManager());

}

rp3d::PhysicsWorld *World::GetPhysicsWorld() const
{
    return _physicsWorld;
}

void World::Clear()
{
    std::vector<Entity> entities = _entityManager->GetEntities();
    for (const Entity &entity : entities)
    {
        _entityManager->Destroy(entity);
    }
}

Entity World::CreateEntity(const std::string &name) const
{
    Entity id = _entityManager->Create();
    AddComponent(id, Component::Name{name});
    return id;
}

Entity World::CreateEntity() const
{
    Entity id = _entityManager->Create();
    return id;
}

void World::DestroyEntity(Entity id)
{
    _entityManager->Destroy(id);
    _componentManager->EntityDestroyed(id);
    _systemManager->EntityDestroyed(id);
}
