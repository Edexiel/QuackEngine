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
    void init();

    // Entity methods
    Entity &createEntity(std::string name);
    void destroyEntity(Entity &entity);

    // Component methods
    template<typename T>
    void registerComponent();

    template<typename T>
    void addComponent(Entity &entity, T component);

    template<typename T>
    void removeComponent(Entity &entity);

    template<typename T>
    T &getComponent(Entity &entity);

    template<typename T>
    ComponentType getComponentType();


    // System methods
    template<typename T>
    std::shared_ptr<T> registerSystem();

    template<typename T>
    void setSystemSignature(Signature signature);
};

void Ecs::init()
{
    _componentManager = std::make_unique<ComponentManager>();
    _entityManager = std::make_unique<EntityManager>();
    _systemManager = std::make_unique<SystemManager>();
}

Entity &Ecs::createEntity(std::string name)
{
    return _entityManager->create(name);
}

void Ecs::destroyEntity(Entity &entity)
{
    _entityManager->destroy(entity.getId());
    _componentManager->entityDestroyed(entity.getId());
    _systemManager->entityDestroyed(entity.getId());
}

template<typename T>
void Ecs::registerComponent()
{
    _componentManager->registerComponent<T>();
}

template<typename T>
void Ecs::addComponent(Entity &entity, T component)
{
    _componentManager->addComponent<T>(entity.getId(), component);

    auto signature = _entityManager->getSignature(entity.getId());
    signature.set(_componentManager->getComponentType<T>(), true);
    _entityManager->setSignature(entity.getId(), signature);

    _systemManager->entitySignatureChanged(entity.getId(), signature);
}

template<typename T>
void Ecs::removeComponent(Entity &entity)
{
    _componentManager->removeComponent<T>(entity.getId());

    auto signature = _entityManager->getSignature(entity.getId());
    signature.set(_componentManager->getComponentType<T>(), false);

    _entityManager->setSignature(entity.getId(), signature);
    _systemManager->entitySignatureChanged(entity.getId(), signature);
}

template<typename T>
T &Ecs::getComponent(Entity &entity)
{
    return _componentManager->getComponent<T>(entity.getId());
}

template<typename T>
ComponentType Ecs::getComponentType()
{
    return _componentManager->getComponentType<T>();
}

template<typename T>
std::shared_ptr<T> Ecs::registerSystem()
{
    return _systemManager->registerSystem<T>();
}

template<typename T>
void Ecs::setSystemSignature(Signature signature)
{
    _systemManager->setSignature<T>(signature);
}


#endif //QUACKENGINE_ECS_HPP
