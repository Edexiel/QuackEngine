//
// Created by lemome on 16/03/2021.
//

#ifndef QUACKENGINE_ENTITYMANAGER_HPP
#define QUACKENGINE_ENTITYMANAGER_HPP

#include <vector>
#include <unordered_map>
#include <bitset>
#include <algorithm>

#include "Entity.hpp"
#include "Types.hpp"
#include "Debug/Assertion.hpp"


class EntityManager
{
private:
    EntityId _idCount;

    std::vector<Entity> _entities{};
public:
    const std::vector<Entity> &GetEntities() const;

private:
    std::vector<Signature> _signatures{};

    std::unordered_map<EntityId, size_t> _entityLut{};

public:
    EntityManager();

    Entity &Create(std::string &name);

    Entity &Get(EntityId id);

    Signature GetSignature(EntityId id);

    void SetSignature(EntityId id, Signature signature);

    void Destroy(EntityId id);
};

/**
 * Entity constructor
 */
 inline EntityManager::EntityManager()
{
    _entityLut.reserve(START_SIZE);     //lookup table to translate faster Entity id to index in array
    _entities.reserve(START_SIZE);      //Entity array
    _signatures.reserve(START_SIZE);    // Signature array
}

/**
 * Instantiate a new entity and add it to the lookup table
 * @param name Entity's name
 * @return Reference to entity
 */
inline Entity &EntityManager::Create(std::string &name)
{
    Entity &e = _entities.emplace_back(_idCount++, std::move(name));
    _signatures.emplace_back();
    _entityLut.insert({e.GetId(), _entities.size() - 1});

    return e;
}

/**
 * Get a pointer to an Entity by providing an id
 * @param id Entity's id
 * @return A valid pointer to an entity or nullptr if no Entity is associated to id (do not store, lifetime not garanteed)
 */
inline Entity &EntityManager::Get(EntityId id)
{
    Assert_Fatal_Error(_entityLut.find(id) != _entityLut.end(), "Entity id does not exists");
    return _entities[_entityLut[id]];
}

/**
 * Removes an Entity by id
 * @param id
 */
inline void EntityManager::Destroy(EntityId id)
{
    Assert_Error(_entityLut.find(id) != _entityLut.end(), "Entity id does not exists");

    size_t index = _entityLut[id]; //index of the entity and signature
    EntityId backId = _entities.back().GetId();

    std::swap(_entities[index], _entities.back());
    _entities.pop_back();

    std::swap(_signatures[index], _signatures.back());
    _signatures.pop_back();

/* Since we swapped for the back entity
 * we set the index of this entity to the index of the previous one
 */
    _entityLut[backId] = index;
    _entityLut.erase(id);

}

/**
 * Get the signature of an Entity by id, a signature is a bitfield which contains components registration
 * @param id
 * @return The signature of the entity
 */
inline Signature EntityManager::GetSignature(EntityId id)
{
    Assert_Fatal_Error(_entityLut.find(id) != _entityLut.end(), "Entity id does not exists");

    return _signatures[_entityLut[id]];

}

/**
 * Sets the signature of an entity
 * @param id
 * @param signature
 */
inline void EntityManager::SetSignature(EntityId id, Signature signature)
{
    Assert_Error(_entityLut.find(id) != _entityLut.end(), "Entity id does not exists");

    _signatures[_entityLut[id]] = signature;
}

inline const std::vector<Entity> &EntityManager::GetEntities() const
{
    return _entities;
}

#endif //QUACKENGINE_ENTITYMANAGER_HPP
