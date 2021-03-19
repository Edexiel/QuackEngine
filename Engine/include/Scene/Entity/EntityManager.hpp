//
// Created by lemome on 16/03/2021.
//

#ifndef QUACKENGINE_ENTITYMANAGER_HPP
#define QUACKENGINE_ENTITYMANAGER_HPP

#include <vector>
#include <unordered_map>
#include <bitset>

#include "Scene/Entity/Entity.hpp"

const std::uint32_t COMPONENTS_NUMBER = 3;
typedef std::bitset<COMPONENTS_NUMBER> Signature;

class EntityManager
{
private:
    std::vector<Entity> _entities;
    std::vector<Signature> _signatures;
    std::unordered_map<EntityId, size_t> _entityLut;
    std::unordered_map<EntityId, std::bitset<COMPONENTS_NUMBER>> _entityComp;

public:
    EntityManager();
    Entity &instantiate(const std::string &name);
    Entity *get(EntityId id);
    Signature getSignature(EntityId id);
    void setSignature(EntityId id, Signature signature);
    void remove(EntityId id);
};


#endif //QUACKENGINE_ENTITYMANAGER_HPP
