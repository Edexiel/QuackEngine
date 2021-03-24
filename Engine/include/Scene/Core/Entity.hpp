#ifndef QUACKENGINE_ENTITY_HPP
#define QUACKENGINE_ENTITY_HPP

#include <queue>
#include <string>
#include <utility>
#include "Types.hpp"

class Entity
{
private:
    static EntityId _idCount;
    static std::queue<EntityId> _garbage;

    EntityId _id;
    std::string _name;

    static unsigned int GetIdCount();

public:
    Entity() = delete;

    explicit Entity(EntityId id, std::string name);

    Entity(EntityId id, const std::string &name);

    ~Entity();

    [[nodiscard]]
    EntityId GetId() const;

    [[nodiscard]]
    const std::string &GetName() const;
};

EntityId Entity::_idCount = 0;
std::queue<EntityId> Entity::_garbage{};

Entity::Entity(EntityId id, const std::string &name) : _id(id), _name(name)
{}

Entity::Entity(std::string name) : _name(std::move(name))
{
    if (!_garbage.empty()) {
        _id = _garbage.front();
        _garbage.pop();
        return;
    }
    _id = _idCount++;
}

Entity::~Entity()
{
    _garbage.push(_id);
}

inline EntityId Entity::GetId() const
{
    return _id;
}

inline const std::string &Entity::GetName() const
{
    return _name;
}

unsigned int Entity::GetIdCount()
{
    return _idCount;
}


#endif // QUACKENGINE_ENTITY_HPP
