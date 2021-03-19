#ifndef QUACKENGINE_ENTITY_HPP
#define QUACKENGINE_ENTITY_HPP

#include <cstdint>
#include <queue>
#include <string>
#include <utility>

typedef std::int_fast64_t EntityId;

class Entity
{
private:
    static EntityId _idCount;
    static std::queue<EntityId> _garbage;

    EntityId _id;
    std::string _name;

    static unsigned int getIdCount();

public:
    Entity() = delete;

    Entity(std::string name);
    ~Entity();

    EntityId getId() const;
    std::string getName() const;
};

EntityId Entity::_idCount = 0;

Entity::Entity(std::string name) : _name(std::move(name))
{
    if (!_garbage.empty())
    {
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

inline EntityId Entity::getId() const
{
    return _id;
}

inline std::string Entity::getName() const
{
    return _name;
}

unsigned int Entity::getIdCount()
{
    return _idCount;
}


#endif // QUACKENGINE_ENTITY_HPP
