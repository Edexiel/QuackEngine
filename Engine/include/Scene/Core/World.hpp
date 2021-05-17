#ifndef QUACKENGINE_WORLD_HPP
#define QUACKENGINE_WORLD_HPP

#include <utility>

#include "Types.hpp"

#include "Scene/Core/EntityManager.hpp"
#include "Scene/Core/SystemManager.hpp"
#include "Scene/Core/ComponentManager.hpp"
#include "Physics/PhysicsEventManager.hpp"

#include "Scene/Component/Name.hpp"
#include <string_view>

namespace reactphysics3d
{
    class PhysicsWorld;
}

class World
{
private:
    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<SystemManager> _systemManager;
public:
    const std::unique_ptr<SystemManager> &GetSystemManager() const;
private:

    reactphysics3d::PhysicsWorld *_physicsWorld = nullptr;

    std::string_view _name;


public:
    World() = delete;
    explicit World(std::string_view &name);

    void Init();

    void Clear();

    // Entity methods
    Entity CreateEntity(std::string name);

    void DestroyEntity(Entity id);

    // Component methods
    template<typename T>
    void RegisterComponent();

    template<typename T>
    void AddComponent(Entity id, T component);

    template<typename T>
    void RemoveComponent(Entity id);

    template<typename T>
    T &GetComponent(Entity id);

    template<typename T>
    bool HasComponent(Entity id);

    template<typename T>
    ComponentType GetComponentType();

    // System methods
    template<typename T>
    std::shared_ptr<T> RegisterSystem();

    template<typename T>
    void SetSystemSignature(Signature signature);

    reactphysics3d::PhysicsWorld *GetPhysicsWorld() const;

    const std::string_view &GetName() const;

    const std::unique_ptr<EntityManager> &GetEntityManager() const;

};

inline reactphysics3d::PhysicsWorld *World::GetPhysicsWorld() const
{
    return _physicsWorld;
}

inline void World::Clear()
{
    //todo:
}

inline Entity World::CreateEntity(std::string name)
{
    Entity id = _entityManager->Create();
    AddComponent(id, Component::Name{std::move(name)});
    return id;
}

inline void World::DestroyEntity(Entity id)
{
    _entityManager->Destroy(id);
    _componentManager->EntityDestroyed(id);
    _systemManager->EntityDestroyed(id);
}

template<typename T>
inline void World::RegisterComponent()
{
    _componentManager->RegisterComponent<T>();
}

template<typename T>
inline void World::AddComponent(Entity id, T component) //todo: maybe pass by const ref
{
    _componentManager->AddComponent<T>(id, component);

    auto signature = _entityManager->GetSignature(id);
    signature.set(_componentManager->GetComponentType<T>(), true);
    _entityManager->SetSignature(id, signature);

    _systemManager->EntitySignatureChanged(id, signature);
}

template<typename T>
inline void World::RemoveComponent(Entity id)
{
    _componentManager->RemoveComponent<T>(id);

    auto signature = _entityManager->GetSignature(id);
    signature.set(_componentManager->GetComponentType<T>(), false);

    _entityManager->SetSignature(id, signature);
    _systemManager->EntitySignatureChanged(id, signature);
}

template<typename T>
inline T &World::GetComponent(Entity id)
{
    return _componentManager->GetComponent<T>(id);
}

template<typename T>
inline bool World::HasComponent(Entity id)
{
    return _componentManager->HasComponent<T>(id);
}

template<typename T>
inline ComponentType World::GetComponentType()
{
    return _componentManager->GetComponentType<T>();
}

template<typename T>
inline std::shared_ptr<T> World::RegisterSystem()
{
    return _systemManager->RegisterSystem<T>();
}

template<typename T>
inline void World::SetSystemSignature(Signature signature)
{
    _systemManager->SetSignature<T>(signature);
}

inline const std::string_view &World::GetName() const
{
    return _name;
}


inline const std::unique_ptr<EntityManager> &World::GetEntityManager() const
{
    return _entityManager;
}

inline const std::unique_ptr<SystemManager> &World::GetSystemManager() const
{
    return _systemManager;
}

#endif //QUACKENGINE_WORLD_HPP
