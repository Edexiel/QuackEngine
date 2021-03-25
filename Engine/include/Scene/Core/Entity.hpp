#ifndef QUACKENGINE_ENTITY_HPP
#define QUACKENGINE_ENTITY_HPP

#include <string>
#include <utility>
#include "Types.hpp"

class Entity
{
private:

    EntityId _id;
    std::string _name;

public:
    Entity() = delete;
    Entity(EntityId id, std::string &&name);

    [[nodiscard]]
    EntityId GetId() const;

    [[nodiscard]]
    const std::string &GetName() const;

    void SetName(const std::string &name);
};


inline Entity::Entity(EntityId id, std::string &&name) : _id(id), _name(name)
{}

inline EntityId Entity::GetId() const
{
    return _id;
}

inline const std::string &Entity::GetName() const
{
    return _name;
}

inline void Entity::SetName(const std::string &name)
{
    _name = name;
}


#endif // QUACKENGINE_ENTITY_HPP
