//
// Created by gnisi on 22/03/2021.
//

#ifndef QUACKENGINE_SYSTEMMANAGER_HPP
#define QUACKENGINE_SYSTEMMANAGER_HPP

#include <memory>
#include <unordered_map>

#include "Types.hpp"
#include "System.hpp"
#include "Debug/Assertion.hpp"

class SystemManager
{
private:
    std::unordered_map<const char *, Signature> _signatures;
    std::unordered_map<const char *, std::shared_ptr<System>> _systems;

public:
    template<typename T>
    std::shared_ptr<T> registerSystem();
    template<typename T>
    void setSignature(Signature signature);

    void entityDestroyed(EntityId id);
    void entitySignatureChanged(EntityId id, Signature entitySignature);

};

template<typename T>
std::shared_ptr<T> SystemManager::registerSystem()
{
    const char *typeName = typeid(T).name();
    Assert_Fatal_Error(_systems.find(typeName) != _systems.end(), "Registering system more than once.");

    auto system = std::make_shared<T>();
    _systems.insert({typeName, system});
    return system;

}

template<typename T>
void SystemManager::setSignature(Signature signature)
{
    const char *typeName = typeid(T).name();
    Assert_Fatal_Error(_systems.find(typeName) != _systems.end(), "System used before registered.");

    _signatures.insert({typeName, signature});

}

void SystemManager::entityDestroyed(EntityId id)
{
    for (auto const &pair : _systems)
    {
        auto const &system = pair.second;

        system->_entities.erase(id);
    }

}

void SystemManager::entitySignatureChanged(EntityId id, Signature entitySignature)
{
    for (auto const &pair : _systems)
    {
        auto const &type = pair.first;
        auto const &system = pair.second;
        auto const &systemSignature = _signatures[type];

        if ((entitySignature & systemSignature) == systemSignature)
        {
            system->_entities.insert(id);
        } else
        {
            system->_entities.erase(id);
        }
    }

}


#endif //QUACKENGINE_SYSTEMMANAGER_HPP
