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
    std::shared_ptr<ComponentArray<T>> GetComponentArray();

public:
    template<typename T>
    void RegisterComponent();

    template<typename T>
    ComponentType GetComponentType();

    template<typename T>
    void AddComponent(EntityId id, T component);

    template<typename T>
    void RemoveComponent(EntityId id);

    template<typename T>
    T &GetComponent(EntityId id);

    void EntityDestroyed(EntityId id);
};

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
{
    const char *typeName = typeid(T).name();
    Assert_Fatal_Error(_componentTypes.find(typeName) != _componentTypes.end(), "Component not registered before use.");
    return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
}

template<typename T>
void ComponentManager::RegisterComponent()
{

    const char *typeName = typeid(T).name();

    Assert_Fatal_Error(_componentTypes.find(typeName) != _componentTypes.end(),
                       "Registering component type more than once.");

    // Add this component type to the component type map
    (void)_componentTypes.insert({typeName, _nextType});

    // Create a ComponentArray pointer and add it to the component arrays map
    _componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    // Increment the value so that the next component registered will be different
    _nextType++;
}

template<typename T>
ComponentType ComponentManager::GetComponentType()
{
    const char *typeName = typeid(T).name();
    Assert_Fatal_Error(_componentTypes.find(typeName) != _componentTypes.end(), "Component not registered before use.");
    return _componentTypes[typeName];
}

template<typename T>
void ComponentManager::AddComponent(EntityId id, T component)
{
    GetComponentArray<T>()->AddData(id, component);
}

template<typename T>
void ComponentManager::RemoveComponent(EntityId id)
{
    GetComponentArray<T>()->RemoveData(id);
}

template<typename T>
T &ComponentManager::GetComponent(EntityId id)
{
    return GetComponentArray<T>()->GetData(id);
}

inline void ComponentManager::EntityDestroyed(EntityId id)
{
    for (auto const &pair : _componentArrays) {
        auto const &component = pair.second;

        component->EntityDestroyed(id);
    }
}

#endif //QUACKENGINE_COMPONENTMANAGER_HPP
