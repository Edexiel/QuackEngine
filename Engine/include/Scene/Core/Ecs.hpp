//
// Created by gnisi on 22/03/2021.
//

#ifndef QUACKENGINE_ECS_HPP
#define QUACKENGINE_ECS_HPP

#include "Types.hpp"
#include "Scene/Core/Entity.hpp"
#include "Scene/Core/EntityManager.hpp"
#include "Scene/Core/SystemManager.hpp"
#include "Scene/Core/ComponentManager.hpp"

class Ecs
{
private:
    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<SystemManager> _systemManager;

public:
    void Init();

    // Entity methods
    Entity &CreateEntity(std::string name);

    void DestroyEntity(Entity &entity);

    // Component methods
    template<typename T>
    void RegisterComponent();

    template<typename T>
    void AddComponent(Entity &entity, T component);

    template<typename T>
    void RemoveComponent(Entity &entity);

    template<typename T>
    T &GetComponent(EntityId &entity);

    template<typename T>
    ComponentType GetComponentType();

    // System methods
    template<typename T>
    std::shared_ptr<T> RegisterSystem();

    template<typename T>
    void SetSystemSignature(Signature signature);
};

inline void Ecs::Init()
{
    _componentManager = std::make_unique<ComponentManager>();
    _entityManager = std::make_unique<EntityManager>();
    _systemManager = std::make_unique<SystemManager>();
}

inline Entity &Ecs::CreateEntity(std::string name)
{
    return _entityManager->Create(name);
}

inline void Ecs::DestroyEntity(Entity &entity)
{
    _entityManager->Destroy(entity.GetId());
    _componentManager->EntityDestroyed(entity.GetId());
    _systemManager->EntityDestroyed(entity.GetId());
}

template<typename T>
void Ecs::RegisterComponent()
{
    _componentManager->RegisterComponent<T>();
}

template<typename T>
void Ecs::AddComponent(Entity &entity, T component)
{
    _componentManager->AddComponent<T>(entity.GetId(), component);

    auto signature = _entityManager->GetSignature(entity.GetId());
    signature.set(_componentManager->GetComponentType<T>(), true);
    _entityManager->SetSignature(entity.GetId(), signature);

    _systemManager->EntitySignatureChanged(entity.GetId(), signature);
}

template<typename T>
void Ecs::RemoveComponent(Entity &entity)
{
    _componentManager->RemoveComponent<T>(entity.GetId());

    auto signature = _entityManager->GetSignature(entity.GetId());
    signature.set(_componentManager->GetComponentType<T>(), false);

    _entityManager->SetSignature(entity.GetId(), signature);
    _systemManager->EntitySignatureChanged(entity.GetId(), signature);
}

template<typename T>
T &Ecs::GetComponent(EntityId &entity)
{
    return _componentManager->GetComponent<T>(entity);
}

template<typename T>
ComponentType Ecs::GetComponentType()
{
    return _componentManager->GetComponentType<T>();
}

template<typename T>
std::shared_ptr<T> Ecs::RegisterSystem()
{
    return _systemManager->RegisterSystem<T>();
}

template<typename T>
void Ecs::SetSystemSignature(Signature signature)
{
    _systemManager->SetSignature<T>(signature);
}

#endif //QUACKENGINE_ECS_HPP
