//
// Created by gnisi on 19/03/2021.
//

#ifndef QUACKENGINE_COMPONENTMANAGER_HPP
#define QUACKENGINE_COMPONENTMANAGER_HPP

#include <unordered_map>
#include <memory>

#include "Types.hpp"
#include "ComponentArray.hpp"

#include "Debug/Assertion.hpp"

class ComponentManager
{
private:
    std::unordered_map<const char *, ComponentType> _componentTypes;
    std::unordered_map<const char *, std::shared_ptr<IComponentArray>> _componentArrays;

    ComponentType _nextType;

    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray();

public:
    template<typename T>
    void registerComponent();

    template<typename T>
    ComponentType getComponentType();

    template<typename T>
    void addComponent(EntityId id, T component);

    template<typename T>
    void removeComponent(EntityId id);

    template<typename T>
    T &getComponent(EntityId id);

    void entityDestroyed(EntityId id);
};

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::getComponentArray()
{
    const char *typeName = typeid(T).name();
    Assert_Fatal_Error(_componentTypes.find(typeName) != _componentTypes.end(), "Component not registered before use.");
    return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
}

template<typename T>
void ComponentManager::registerComponent()
{

    const char *typeName = typeid(T).name();

    Assert_Fatal_Error(_componentTypes.find(typeName) != _componentTypes.end(),
                       "Registering component type more than once.");

    // Add this component type to the component type map
    _componentTypes.insert({typeName, _nextType});

    // Create a ComponentArray pointer and add it to the component arrays map
    _componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    // Increment the value so that the next component registered will be different
    _nextType++;
}

template<typename T>
ComponentType ComponentManager::getComponentType()
{
    const char *typeName = typeid(T).name();
    Assert_Fatal_Error(_componentTypes.find(typeName) != _componentTypes.end(), "Component not registered before use.");
    return _componentTypes[typeName];
}

template<typename T>
void ComponentManager::addComponent(EntityId id, T component)
{
    getComponentArray<T>()->addData(id, component);
}

template<typename T>
void ComponentManager::removeComponent(EntityId id)
{
    getComponentArray<T>()->removeData(id);
}

template<typename T>
T &ComponentManager::getComponent(EntityId id)
{
    return getComponentArray<T>()->getData(id);
}

void ComponentManager::entityDestroyed(EntityId id)
{
    for (auto const &pair : _componentArrays)
    {
        auto const &component = pair.second;

        component->EntityDestroyed(id);
    }
}


#endif //QUACKENGINE_COMPONENTMANAGER_HPP
