//
// Created by lemome on 16/03/2021.
//

#ifndef QUACKENGINE_ENTITYMANAGER_HPP
#define QUACKENGINE_ENTITYMANAGER_HPP

#include <vector>
#include <unordered_map>

#include "Scene/Entity/Entity.hpp"

class EntityManager
{
private:
    std::vector<Entity> _entities;
    std::unordered_map<EntityId,size_t> _entityLut;
public:
    EntityManager();
    Entity& instantiate(const std::string& name);
    Entity * get(EntityId id);
    void remove(EntityId id);
};


#endif //QUACKENGINE_ENTITYMANAGER_HPP
