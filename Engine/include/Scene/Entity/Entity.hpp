#ifndef QUACKENGINE_ENTITY_HPP
#define QUACKENGINE_ENTITY_HPP

#include <cstdint>

typedef std::uint32_t EntityId;

class Entity
{
private:
    static EntityId _idCount;
    unsigned int _id;
    const char *_name;

    static unsigned int getIdCount();

public:
    Entity() = delete;
    Entity(const char *name);
    ~Entity();

    EntityId getId() const;
    const char * getName() const;
};

unsigned int Entity::_idCount = 0;

Entity::Entity(const char *name) : _name(name)
{ _id = _idCount++; }

Entity::~Entity()
{
    // delete all components associated ?
    // add itself to garbage for recycling
}

inline unsigned int Entity::getId() const
{ return _id; }

inline const char *Entity::getName() const
{ return _name; }

unsigned int Entity::getIdCount()
{
    return _idCount;
}

#endif // QUACKENGINE_ENTITY_HPP
