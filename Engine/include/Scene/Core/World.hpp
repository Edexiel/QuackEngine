//
// Created by gnisi on 22/03/2021.
//

#ifndef QUACKENGINE_WORLD_HPP
#define QUACKENGINE_WORLD_HPP

#include <utility>

#include "Types.hpp"
#include "Scene/Core/EntityManager.hpp"
#include "Scene/Core/SystemManager.hpp"
#include "Scene/Core/ComponentManager.hpp"
#include "Scene/Component/Name.hpp"

class World
{
private:

    static World _instance;

    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<SystemManager> _systemManager;

public:
    static World &Instance();

    void Init();

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
};

World World::_instance = World();

inline World &World::Instance()
{
    return _instance;
}

inline void World::Init()
{
    _componentManager = std::make_unique<ComponentManager>();
    _entityManager = std::make_unique<EntityManager>();
    _systemManager = std::make_unique<SystemManager>();

    _componentManager->RegisterComponent<Name>();
}

inline Entity World::CreateEntity(std::string name)
{
    Entity id = _entityManager->Create();
    AddComponent(id, Name{std::move(name)});
    return id;
}

inline void World::DestroyEntity(Entity id)
{
    _entityManager->Destroy(id);
    _componentManager->EntityDestroyed(id);
    _systemManager->EntityDestroyed(id);
}

template<typename T>
void World::RegisterComponent()
{
    _componentManager->RegisterComponent<T>();
}

template<typename T>
void World::AddComponent(Entity id, T component)
{
    _componentManager->AddComponent<T>(id, component);

    auto signature = _entityManager->GetSignature(id);
    signature.set(_componentManager->GetComponentType<T>(), true);
    _entityManager->SetSignature(id, signature);

    _systemManager->EntitySignatureChanged(id, signature);
}

template<typename T>
void World::RemoveComponent(Entity id)
{
    _componentManager->RemoveComponent<T>(id);

    auto signature = _entityManager->GetSignature(id);
    signature.set(_componentManager->GetComponentType<T>(), false);

    _entityManager->SetSignature(id, signature);
    _systemManager->EntitySignatureChanged(id, signature);
}

template<typename T>
T &World::GetComponent(Entity id)
{
    return _componentManager->GetComponent<T>(id);
}

template<typename T>
ComponentType World::GetComponentType()
{
    return _componentManager->GetComponentType<T>();
}

template<typename T>
std::shared_ptr<T> World::RegisterSystem()
{
    return _systemManager->RegisterSystem<T>();
}

template<typename T>
void World::SetSystemSignature(Signature signature)
{
    _systemManager->SetSignature<T>(signature);
}


#endif //QUACKENGINE_WORLD_HPP
