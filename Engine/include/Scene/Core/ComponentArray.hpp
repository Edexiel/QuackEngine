//
// Created by gnisi on 19/03/2021.
//

#ifndef QUACKENGINE_COMPONENTARRAY_HPP
#define QUACKENGINE_COMPONENTARRAY_HPP

#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Debug/Assertion.hpp"

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;

    virtual void EntityDestroyed(Entity id) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
private:
    std::unordered_map<Entity, size_t> _entityToIndex;
    std::unordered_map<size_t, Entity> _indexToEntity;
    std::vector<T> _components;

public:
    void AddData(Entity id, T &data);

    void DeleteData(Entity id);

    T &GetData(Entity id);

    void EntityDestroyed(Entity id) override;

};

template<typename T>
void ComponentArray<T>::AddData(Entity id, T &data)
{
    size_t end = _components.size();
    _components.emplace_back(std::move(data));
    (void) _entityToIndex.insert({id, end});
    (void) _indexToEntity.insert({end, id});
}

template<typename T>
void ComponentArray<T>::DeleteData(Entity id)
{
    Assert_Fatal_Error(_entityToIndex.find(id) != _entityToIndex.end(), "Removing non-existent component.");

    size_t indexDelete = _entityToIndex[id];
    size_t indexEnd = _components.size() - 1;

    std::swap(_components[indexDelete], _components[indexEnd]);

    Entity entityEnd = _indexToEntity[indexEnd];
    _entityToIndex[entityEnd] = indexDelete;
    _indexToEntity[indexDelete] = entityEnd;

    (void) _entityToIndex.erase(id);
    (void) _indexToEntity.erase(indexEnd);

    _components.pop_back();

}

template<typename T>
T &ComponentArray<T>::GetData(Entity id)
{
    Assert_Fatal_Error(_entityToIndex.find(id) == _entityToIndex.end(), "Retrieving non-existent component.");

    return _components[_entityToIndex[id]];
}

template<typename T>
void ComponentArray<T>::EntityDestroyed(Entity id)
{
    if (_indexToEntity.find(id) != _indexToEntity.end()) {
        DeleteData(id);
    }
}

#endif //QUACKENGINE_COMPONENTARRAY_HPP
