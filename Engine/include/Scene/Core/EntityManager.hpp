#ifndef QUACKENGINE_ENTITYMANAGER_HPP
#define QUACKENGINE_ENTITYMANAGER_HPP

#include <vector>
#include <unordered_map>
#include <bitset>
#include <algorithm>

#include "Types.hpp"
#include "Debug/Assertion.hpp"


class EntityManager
{
private:
    Entity _idCount {0};
    std::vector<Entity> _entities{};

    std::vector<Signature> _signatures{};

    std::unordered_map<Entity, size_t> _entityLut{};


public:
    EntityManager();

    Entity Create();

    Signature GetSignature(Entity id) const;

    std::vector<Entity> &GetEntities();


    void SetSignature(Entity id, Signature signature);

    void Destroy(Entity id);
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
 * @return Reference to entity
 */
inline Entity EntityManager::Create()
{
    Entity id = _entities.emplace_back(_idCount++);
    _signatures.emplace_back();
    _entityLut.insert({id, _entities.size() - 1});

    return id;
}

/**
 * Removes an Entity by id
 * @param id
 */
inline void EntityManager::Destroy(Entity id)
{
    Assert_Error(_entityLut.find(id) == _entityLut.end(), "Entity id does not exists {}",id);

    size_t index = _entityLut[id]; //index of the entity and signature
    Entity backId = _entities.back();

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
inline Signature EntityManager::GetSignature(Entity id) const
{
    Assert_Fatal_Error(_entityLut.find(id) == _entityLut.end(), "Entity id does not exists");

    return _signatures.at(_entityLut.at(id));

}

/**
 * Sets the signature of an entity
 * @param id
 * @param signature
 */
inline void EntityManager::SetSignature(Entity id, Signature signature)
{
    Assert_Error(_entityLut.find(id) == _entityLut.end(), "Entity id does not exists");

    _signatures[_entityLut[id]] = signature;
}

inline std::vector<Entity> &EntityManager::GetEntities()
{
    return _entities;
}

#endif //QUACKENGINE_ENTITYMANAGER_HPP
