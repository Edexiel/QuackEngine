//
// Created by gnisi on 22/03/2021.
//

#ifndef QUACKENGINE_ECS_HPP
#define QUACKENGINE_ECS_HPP

#include "Scene/Types.hpp"

#include "Scene/Entity/EntityManager.hpp"
#include "Scene/System/SystemManager.hpp"
#include "Scene/Component/ComponentManager.hpp"


class Ecs
{
private:
    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<SystemManager> _systemManager;

public:
    void Init();

    // Entity methods
    Entity createEntity(std::string &name);
    void destroyEntity(EntityId id);

    // Component methods
    template<typename T>
    void registerComponent();

    template<typename T>
    void addComponent(EntityId id, T component);

    template<typename T>
    void removeComponent(EntityId id);

    template<typename T>
    T &getComponent(EntityId id);

    template<typename T>
    ComponentType GetComponentType();


    // System methods
    template<typename T>
    std::shared_ptr<T> RegisterSystem();

    template<typename T>
    void SetSystemSignature(Signature signature);
};

void Ecs::Init()
{
    _componentManager = std::make_unique<ComponentManager>();
    _entityManager = std::make_unique<EntityManager>();
    _systemManager = std::make_unique<SystemManager>();
}

Entity Ecs::createEntity(std::string &name)
{
    return _entityManager->create(name);
}

void Ecs::destroyEntity(EntityId id)
{
    _entityManager->destroy(id);
    _componentManager->entityDestroyed(id);
    _systemManager->entityDestroyed(id);
}

template<typename T>
void Ecs::registerComponent()
{
    _componentManager->registerComponent<T>();
}

template<typename T>
void Ecs::addComponent(EntityId id, T component)
{
    _componentManager->addComponent<T>(id, component);

    auto signature = _entityManager->getSignature(id);
    signature.set(_componentManager->getComponentType<T>(), true);
    _entityManager->setSignature(id, signature);

    _systemManager->entitySignatureChanged(id, signature);
}

template<typename T>
void Ecs::removeComponent(EntityId id)
{
    _componentManager->removeComponent<T>(id);

    auto signature = _entityManager->getSignature(id);
    signature.set(_componentManager->getComponentType<T>(), false);

    _entityManager->setSignature(id, signature);
    _systemManager->entitySignatureChanged(id, signature);
}

template<typename T>
T &Ecs::getComponent(EntityId entity)
{
    return _componentManager->getComponent<T>(entity);
}

template<typename T>
ComponentType Ecs::GetComponentType()
{
    return _componentManager->getComponentType<T>();
}

template<typename T>
std::shared_ptr<T> Ecs::RegisterSystem()
{
    return _systemManager->registerSystem<T>();
}

template<typename T>
void Ecs::SetSystemSignature(Signature signature)
{
    _systemManager->setSignature<T>(signature);
}


#endif //QUACKENGINE_ECS_HPP
