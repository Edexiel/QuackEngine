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

const size_t START_SIZE = 1000;

class EntityManager
{
private:
    std::vector<Entity> _entities;
    std::vector<Signature> _signatures;
    std::unordered_map<EntityId, size_t> _entityLut;
    std::unordered_map<EntityId, std::bitset<COMPONENTS_NUMBER>> _entityComp;

public:
    EntityManager();
    Entity &create(std::string &name);
    Entity &get(EntityId id);
    Signature getSignature(EntityId id);
    void setSignature(EntityId id, Signature signature);
    void destroy(EntityId id);
};

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
Entity &EntityManager::create(std::string &name)
{
    Entity &e = _entities.emplace_back(std::move(name));
    _signatures.emplace_back();
    _entityLut.insert({e.getId(), _entities.size() - 1});

    return e;
}

/**
 * Get a pointer to an Entity by providing an id
 * @param id Entity's id
 * @return A valid pointer to an entity or nullptr if no Entity is associated to id (do not store, lifetime not garanteed)
 */
Entity &EntityManager::get(EntityId id)
{
    Assert_Fatal_Error(_entityLut.find(id) != _entityLut.end(), "Entity id does not exists");
    return _entities[_entityLut[id]];
}

/**
 * Removes an Entity by id
 * @param id
 */
void EntityManager::destroy(EntityId id)
{
    Assert_Error(_entityLut.find(id) != _entityLut.end(), "Entity id does not exists");

    size_t index = _entityLut[id];
    EntityId backId = _entities.back().getId();

    std::swap(_entities[index], _entities.back());
    _entities.pop_back();

    std::swap(_signatures[index], _signatures.back());
    _signatures.pop_back();

    _entityLut[backId] = index;
    _entityLut.erase(id);

}

/**
 * Get the signature of an Entity by id, a signature is a bitfield which contains components registration
 * @param id
 * @return The signature of the entity
 */
Signature EntityManager::getSignature(EntityId id)
{
    Assert_Fatal_Error(_entityLut.find(id) != _entityLut.end(), "Entity id does not exists");

    return _signatures[_entityLut[id]];

}

/**
 * Sets the signature of an entity
 * @param id
 * @param signature
 */
void EntityManager::setSignature(EntityId id, Signature signature)
{
    Assert_Error(_entityLut.find(id) != _entityLut.end(), "Entity id does not exists");

    _signatures[_entityLut[id]] = signature;
}


#endif //QUACKENGINE_ENTITYMANAGER_HPP
