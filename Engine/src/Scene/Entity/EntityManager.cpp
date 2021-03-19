#include "Scene/Entity/EntityManager.hpp"
#include <cstdint>
#include <algorithm>

const size_t START_SIZE = 1000;

EntityManager::EntityManager()
{
    _entities.reserve(START_SIZE);
    _entityLut.reserve(START_SIZE);
}

/**
 * Instantiate a new entity and add it to the lookup table
 * @param name Entity's name
 * @return Reference to entity
 */
Entity &EntityManager::instantiate(const std::string &name)
{
    Entity &e = _entities.emplace_back(name);
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

void EntityManager::remove(EntityId id)
{
    auto it = _entityLut.find(id);

    if (it != _entityLut.end())
    {
        size_t index = it->second;
        EntityId backId = _entities.back().getId();

        std::swap(_entities[index], _entities.back());
        _entities.pop_back();

        _entityLut[backId] = index;
        _entityLut.erase(id);
    }


}