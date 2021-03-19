#include "Scene/Entity/EntityManager.hpp"
#include <cstdint>
#include <algorithm>

const size_t START_SIZE = 1000;

EntityManager::EntityManager()
{
    _entityLut.reserve(START_SIZE); //lookup table to translate faster Entity id to index in array

    _entities.reserve(START_SIZE); //Entity array
    _signatures.reserve(START_SIZE); // Signature array
}

/**
 * Instantiate a new entity and add it to the lookup table
 * @param name Entity's name
 * @return Reference to entity
 */
Entity &EntityManager::instantiate(const std::string &name)
{
    Entity &e = _entities.emplace_back(name);
    _signatures.emplace_back();
    _entityLut.insert({e.getId(), _entities.size() - 1});

    return e;
}

/**
 * Get a pointer to an Entity by providing an id
 * @param id Entity's id
 * @return A valid pointer to an entity or nullptr if no Entity is associated to id
 */
Entity *EntityManager::get(EntityId id)
{
    auto it = _entityLut.find(id);

    if (it != _entityLut.end())
        return &_entities[it->second];

    return nullptr;
}

/**
 * Removes an Entity by id
 * @param id
 */
void EntityManager::remove(EntityId id)
{
    auto it = _entityLut.find(id);

    if (it != _entityLut.end())
    {
        size_t index = it->second;
        EntityId backId = _entities.back().getId();

        std::swap(_entities[index], _entities.back());
        _entities.pop_back();

        std::swap(_signatures[index], _signatures.back());
        _signatures.pop_back();

        _entityLut[backId] = index;
        _entityLut.erase(id);
    }
}

/**
 * Get the signature of an Entity by id, a signature is a bitfield which contains components registration
 * @param id
 * @return The signature of the entity
 */
Signature EntityManager::getSignature(EntityId id)
{
    auto it = _entityLut.find(id);

    if (it != _entityLut.end())
        return _signatures[it->second];

    return Signature{};
}

/**
 * Sets the signature of an entity
 * @param id
 * @param signature
 */
void EntityManager::setSignature(EntityId id, Signature signature)
{
    auto it = _entityLut.find(id);

    if (it != _entityLut.end())
        _signatures[it->second] = signature;
}