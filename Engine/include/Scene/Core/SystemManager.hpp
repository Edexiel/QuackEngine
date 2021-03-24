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
    std::shared_ptr<T> RegisterSystem();

    template<typename T>
    void SetSignature(Signature signature);

    void EntityDestroyed(EntityId id);

    void EntitySignatureChanged(EntityId id, Signature entitySignature);

};

template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem()
{
    const char *typeName = typeid(T).name();
    Assert_Fatal_Error(_systems.find(typeName) != _systems.end(), "Registering system more than once.");

    auto system = std::make_shared<T>();
    _systems.insert({typeName, system});
    return system;

}

template<typename T>
void SystemManager::SetSignature(Signature signature)
{
    const char *typeName = typeid(T).name();
    Assert_Fatal_Error(_systems.find(typeName) != _systems.end(), "System used before registered.");

    (void)_signatures.insert({typeName, signature});

}

void SystemManager::EntityDestroyed(EntityId id)
{
    for (auto const &pair : _systems) {
        auto const &system = pair.second;

        (void)system->_entities.erase(id);
    }

}

void SystemManager::EntitySignatureChanged(EntityId id, Signature entitySignature)
{
    for (auto const &pair : _systems) {
        auto const &type = pair.first;
        auto const &system = pair.second;
        auto const &systemSignature = _signatures[type];

        if ((entitySignature & systemSignature) == systemSignature) {
            (void)system->_entities.insert(id);
        } else {
            (void)system->_entities.erase(id);
        }
    }

}

#endif //QUACKENGINE_SYSTEMMANAGER_HPP
