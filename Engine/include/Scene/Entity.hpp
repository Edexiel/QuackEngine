#ifndef QUACKENGINE_ENTITY_HPP
#define QUACKENGINE_ENTITY_HPP

#include <string>

#define EntityId unsigned int

class Entity {
private:
  static EntityId _idCount;
  unsigned int _id;
  std::string _name;

public:
  Entity() = default;
  Entity(const std::string &name);
  ~Entity();

  EntityId getId() const;
  const std::string &getName() const;
};
unsigned int Entity::_idCount = 0;

Entity::Entity(const std::string &name) : _name(name) { _id = _idCount++; }

Entity::~Entity() {
  // delete all components associated ?
  // add itselt to garbage for recycling
}
inline unsigned int Entity::getId() const { return _id; }

inline const std::string &Entity::getName() const { return _name; }

#endif // QUACKENGINE_ENTITY_HPP
