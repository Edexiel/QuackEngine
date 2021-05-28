
#ifndef QUACKENGINE_COMPONENTMANAGER_HPP
#define QUACKENGINE_COMPONENTMANAGER_HPP

#include <string_view>
#include <unordered_map>
#include <memory>

#include "Types.hpp"
#include "ComponentArray.hpp"
#include "Debug/Assertion.hpp"
#include <Tools/Type.hpp>

#include "Debug/Log.hpp"

 class ComponentManager
{
private:
    std::unordered_map<std::string_view , ComponentType> _componentTypes;
    std::unordered_map<std::string_view , std::shared_ptr<IComponentArray>> _componentArrays;

    ComponentType _nextType =0;

    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray();

public:
    template<typename T>
    void RegisterComponent();

    template<typename T>
    ComponentType GetComponentType();

    template<typename T>
    void AddComponent(Entity id, const T& component);

    template<typename T>
    void RemoveComponent(Entity id);

    template<typename T>
    T &GetComponent(Entity id);
    template<typename T>
    bool HasComponent(Entity id);


    void EntityDestroyed(Entity id);
};

template<typename T>
inline std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
{
    std::string_view typeName = typeid(T).name();

    Assert_Fatal_Error(_componentTypes.find(typeName) == _componentTypes.end(), "Component not registered before use.");
    return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
}

template<typename T>
inline void ComponentManager::RegisterComponent()
{

    std::string_view typeName = typeid(T).name();

    if(_componentTypes.find(typeName)!= _componentTypes.end())
    {
        Log_Warning("Already registered, skipping: {}", demangle(typeid(T).name()));
        return;
    }
    Log_Info("Registering: {}", demangle(typeid(T).name()));

    // Add this component type to the component type map
    _componentTypes.insert({typeName, _nextType});

    // Create a ComponentArray pointer and add it to the component arrays map
    _componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    // Increment the value so that the next component registered will be different
    _nextType++;
}

template<typename T>
inline ComponentType ComponentManager::GetComponentType()
{
    std::string_view typeName = typeid(T).name();
    Assert_Fatal_Error(_componentTypes.find(typeName) == _componentTypes.end(), "Component not registered before use.");
    return _componentTypes[typeName];
}

template<typename T>
inline void ComponentManager::AddComponent(Entity id, const T& component)
{
    GetComponentArray<T>()->AddData(id, component);
}

template<typename T>
inline void ComponentManager::RemoveComponent(Entity id)
{
    GetComponentArray<T>()->DeleteData(id);
}

template<typename T>
inline T &ComponentManager::GetComponent(Entity id)
{
    return GetComponentArray<T>()->GetData(id);
}

 template<typename T>
 inline bool ComponentManager::HasComponent(Entity id)
 {
     return GetComponentArray<T>()->HasData(id);
 }

inline void ComponentManager::EntityDestroyed(Entity id)
{
    for (auto const &pair : _componentArrays) {
        auto const &component = pair.second;

        component->EntityDestroyed(id);
    }
}

#endif //QUACKENGINE_COMPONENTMANAGER_HPP
