#ifndef QUACKENGINE_WORLD_HPP
#define QUACKENGINE_WORLD_HPP

#include "Types.hpp"

#include "Scene/Core/EntityManager.hpp"
#include "Scene/Core/SystemManager.hpp"
#include "Scene/Core/ComponentManager.hpp"

#include "reactphysics3d/reactphysics3d.h"

#include "Scene/Component/Name.hpp"
#include <string>

class World
{
private:
    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<SystemManager> _systemManager;

    rp3d::PhysicsWorld *_physicsWorld = nullptr;

    std::string _name;


public:
    World() = delete;
    explicit World(std::string &name);

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
    ComponentType GetComponentType();

    // System methods
    template<typename T>
    std::shared_ptr<T> RegisterSystem();

    template<typename T>
    void SetSystemSignature(Signature signature);

    rp3d::PhysicsWorld *GetPhysicsWorld() const;

    const std::string &GetName() const;
};

inline rp3d::PhysicsWorld *World::GetPhysicsWorld() const
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
    //AddComponent(id, Name{std::move(name)});
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
inline void World::AddComponent(Entity id, T component)
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

inline const std::string &World::GetName() const
{
    return _name;
}


#endif //QUACKENGINE_WORLD_HPP
