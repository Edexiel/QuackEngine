//
// Created by gnisi on 22/03/2021.
//

#ifndef QUACKENGINE_SYSTEMMANAGER_HPP
#define QUACKENGINE_SYSTEMMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string_view>

#include "Types.hpp"
#include "System.hpp"
#include "Debug/Assertion.hpp"
#include <Tools/Type.hpp>
#include "Debug/Log.hpp"

class SystemManager
{
private:
    std::unordered_map<std::string_view, Signature> _signatures;
    std::unordered_map<std::string_view, std::unique_ptr<System>> _systems;

public:
    template<typename T>
    T* RegisterSystem();

    template<typename T>
    void SetSignature(Signature signature);

    void EntityDestroyed(Entity id);

    void EntitySignatureChanged(Entity id, Signature entitySignature);

    template<typename T>
    T* GetSystem();

};

template<typename T>
T* SystemManager::RegisterSystem()
{
    std::string_view typeName = typeid(T).name();
    auto search = _systems.find(typeName);
    if (search != _systems.end())
    {
        Log_Warning("Already registered, skipping: {}", demangle(typeid(T).name()));
        return static_cast<T*>(search->second.get());
    }

    Log_Info("Registering: {}", demangle(typeid(T).name()));

    auto result =  _systems.insert({typeName, std::make_unique<T>()});

    return static_cast<T*>(result.first->second.get());
}

template<typename T>
void SystemManager::SetSignature(Signature signature)
{
    std::string_view typeName = typeid(T).name();
    Assert_Fatal_Error(_systems.find(typeName) == _systems.end(), "System used before registered.");

    (void) _signatures.insert({typeName, signature});

}

inline void SystemManager::EntityDestroyed(Entity id)
{
    for (auto const &pair : _systems)
    {
        auto const &system = pair.second;

        (void) system->_entities.erase(id);
    }

}

inline void SystemManager::EntitySignatureChanged(Entity id, Signature entitySignature)
{
    for (auto const &pair : _systems)
    {
        auto const &type = pair.first;
        auto const &system = pair.second;
        auto const &systemSignature = _signatures[type];

        if ((entitySignature & systemSignature) == systemSignature)
        {
            (void) system->_entities.insert(id);
        }
        else
        {
            (void) system->_entities.erase(id);
        }
    }

}

template<typename T>
T* SystemManager::GetSystem()
{
    std::string_view typeName = typeid(T).name();
    auto search = _systems.find(typeName);
    if (search != _systems.end())
    {
        return static_cast<T*>(search->second.get());
    }
    return nullptr;
}

#endif //QUACKENGINE_SYSTEMMANAGER_HPP
