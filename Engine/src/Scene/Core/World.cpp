#include "Scene/Core/World.hpp"
#include "Engine.hpp"

#include "Scene/System/RenderSystem.hpp"

World::World(std::string &name) : _name(name)
{
    Engine &engine = Engine::Instance();

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
        DestroyEntity(entity);
    }

    GetSystem<RenderSystem>()->Clear();
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


void World::SetInitGame(InitFn ptr)
{
    InitGamePtr = ptr;
}

void World::SetInitSystems(InitFn ptr)
{
    InitGamePtr = ptr;
}

void World::SetInitSettings(InitFn ptr)
{
    InitSettingsPtr = ptr;
}

void World::SetRegister(InitFn ptr)
{
    RegisterPtr = ptr;
}

void World::SetSave(serializeFn ptr)
{
    SavePtr = ptr;
}

void World::SetLoad(serializeFn ptr)
{
    LoadPtr = ptr;
}

void World::SetBuild(BuildFn ptr)
{
    BuildPtr = ptr;
}

void World::Register()
{
    if (RegisterPtr)
        RegisterPtr(*this);
    else
        Log_Error("No register function bind to world {}", _name);
}

void World::InitGame()
{
    if (InitGamePtr)
        InitGamePtr(*this);
    else
        Log_Error("No init game function bind to world {}", _name);

}

void World::InitSystems()
{
    if (InitSystemsPtr)
        InitSystemsPtr(*this);
    else
        Log_Error("No init systems function bind to world {}", _name);

}

void World::InitSettings()
{
    if (InitSettingsPtr)
        InitSettingsPtr(*this);
    else
        Log_Error("No init settings function bind to world {}", _name);

}

void World::Build(std::map<std::string, bool> &c,Entity id) const
{
    if (BuildPtr)
        BuildPtr(*this,c,id);
    else
        Log_Error("No Build function bind to world {}", _name);
}

