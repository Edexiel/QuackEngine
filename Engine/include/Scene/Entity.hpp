#ifndef QUACKENGINE_ENTITY_HPP
#define QUACKENGINE_ENTITY_HPP

#include <vector>
#include <string>

class Entity {
private:
    static unsigned int _idCount;
    unsigned int _id;
    std::string _name;

public:
    Entity(unsigned int id, const std::string &name);
    ~Entity();

//    template<typename T>
//    std::vector<T> getComponents();
    unsigned int getId() const;
    const std::string &getName() const;
};
unsigned int Entity::_idCount = 0;

Entity::Entity(unsigned int id, const std::string &name) : _name(name)
{
    _id = _idCount++;
}

Entity::~Entity() {
    //delete all components associated ?
    //add itselt to garbage for recycling
}
inline unsigned int Entity::getId() const {
    return _id;
}

inline const std::string &Entity::getName() const {
    return _name;
}



#endif // QUACKENGINE_ENTITY_HPP
