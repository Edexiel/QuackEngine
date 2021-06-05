#include "Scene/Core/World.hpp"

#include <memory>
#include "Engine.hpp"


#include "Scene/Component/EngineComponents.hpp"


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
    Engine &engine = Engine::Instance();

    _componentManager = std::make_unique<ComponentManager>();
    _entityManager = std::make_unique<EntityManager>();
    _systemManager = std::make_unique<SystemManager>();
    engine.GetPhysicsManager().destroyPhysicsWorld(_physicsWorld);

    _physicsWorld = engine.GetPhysicsManager().createPhysicsWorld();
    _physicsWorld->setEventListener(&engine.GetPhysicsEventManager());

    engine.GetInputManager().Clear();

//    std::vector<Entity> entities = _entityManager->GetEntities();
//
//    for (int i = 1; i <= entities.size(); ++i)
//    {
//        DestroyEntity(entities[entities.size() - i]);
//    }

}


Entity World::CreateEntity(const std::string &name) const
{
    Entity id = _entityManager->Create();
    AddComponent(id, Component::Name{name});
    return id;
}

Entity World::CreateEntity() const
{
    return _entityManager->Create();
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
    InitSystemsPtr = ptr;
}

void World::SetInitSettings(InitFn ptr)
{
    InitSettingsPtr = ptr;
}

void World::SetRegister(InitFn ptr)
{
    RegisterPtr = ptr;
}

void World::SetSave(SaveFn ptr)
{
    SavePtr = ptr;
}

void World::SetLoad(LoadFn ptr)
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

void World::Build(std::map<std::string, bool> &c, Entity id) const
{
    if (BuildPtr)
        BuildPtr(*this, c, id);
    else
        Log_Error("No Build function bind to world {}", _name);
}

void World::Save(cereal::JSONOutputArchive &a, const std::map<std::string, bool> &c, Entity id) const
{
    if (SavePtr)
        SavePtr(*this, a, c, id);
    else
        Log_Error("No Save settings function bind to world {}", _name);
}

void World::Load(cereal::JSONInputArchive &a, const std::map<std::string, bool> &c, Entity id) const
{
    if (LoadPtr)
        LoadPtr(*this, a, c, id);
    else
        Log_Error("No Load function bind to world {}", _name);
}


void World::EntityHandler::BuildArray()
{
    build<Component::Name>("Name");
    build<Component::Transform>("Transform");
    build<Component::Camera>("Camera");
    build<Component::Light>("Light");
    build<Component::Model>("Model");
    build<Component::Animator>("Animator");
    build<Component::RigidBody>("RigidBody");
    build<Component::CameraGameplay>("CameraGameplay");
    build<Component::CharacterController>("CharacterController");
    build<Component::ParticleEmitter>("ParticleEmitter");
    build<Component::SimpleShadow>("SimpleShadow");
    world.Build(components, id);
}

void World::EntityHandler::save(cereal::JSONOutputArchive &archive) const
{
    archive(CEREAL_NVP(components));
    write<Component::Name>(archive, id, "Name");
    write<Component::Transform>(archive, id, "Transform");
    write<Component::Camera>(archive, id, "Camera");
    write<Component::Light>(archive, id, "Light");
    write<Component::Model>(archive, id, "Model");
    write<Component::Animator>(archive, id, "Animator");
    write<Component::RigidBody>(archive, id, "RigidBody");
    write<Component::CameraGameplay>(archive, id, "CameraGameplay");
    write<Component::CharacterController>(archive, id, "CharacterController");
    write<Component::ParticleEmitter>(archive, id, "ParticleEmitter");
    write<Component::SimpleShadow>(archive, id, "SimpleShadow");
    world.Save(archive, components, id);
}

void World::EntityHandler::load(cereal::JSONInputArchive &archive)
{
    Entity e = world.CreateEntity();

    archive(CEREAL_NVP(components));

    read<Component::Name>(archive, e, "Name");
    read<Component::Transform>(archive, e, "Transform");
    read<Component::Camera>(archive, e, "Camera");
    read<Component::Light>(archive, e, "Light");
    read<Component::Model>(archive, e, "Model");
    read<Component::Animator>(archive, e, "Animator");
    read<Component::RigidBody>(archive, e, "RigidBody");
    read<Component::CameraGameplay>(archive, e, "CameraGameplay");
    read<Component::CharacterController>(archive, e, "CharacterController");
    read<Component::ParticleEmitter>(archive, e, "ParticleEmitter");
    read<Component::SimpleShadow>(archive, e, "SimpleShadow");
    world.Load(archive, components, e);
}

void World::save(cereal::JSONOutputArchive &archive) const
{
    archive(cereal::make_nvp("name", _name));
    const World &world = *this;
    std::vector<EntityHandler> entities;
    for (Entity &entity : _entityManager->GetEntities())
        entities.emplace_back(entity, world);

    for (auto &item : entities)
        item.BuildArray();

    archive(CEREAL_NVP(entities));
}

void World::load(cereal::JSONInputArchive &archive)
{
    archive(_name);
    std::vector<EntityHandler> entities;

    archive(CEREAL_NVP(entities));
}