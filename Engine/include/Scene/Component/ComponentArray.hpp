//
// Created by gnisi on 19/03/2021.
//

#ifndef QUACKENGINE_COMPONENTARRAY_HPP
#define QUACKENGINE_COMPONENTARRAY_HPP

#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Scene/Entity/Entity.hpp"
#include "Debug/Assertion.hpp"

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(EntityId id) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
private:
    std::unordered_map<EntityId, size_t> _entityToIndex;
    std::unordered_map<size_t, EntityId> _indexToEntity;
    std::vector<T> _components;

public:
    void addData(EntityId id, T &data);
    void deleteData(EntityId id);
    T &getData(EntityId id);
    void EntityDestroyed(EntityId id) override;

};

template<typename T>
void ComponentArray<T>::addData(EntityId id, T &data)
{
    size_t end = _components.size();
    _components.emplace_back(std::move(data));
    _entityToIndex.insert({id, end});
    _indexToEntity.insert({end, id});
}

template<typename T>
void ComponentArray<T>::deleteData(EntityId id)
{
    Assert_Fatal_Error(_entityToIndex.find(id) != _entityToIndex.end(), "Removing non-existent component.");


    size_t indexDelete = _components[_entityToIndex[id]];
    size_t indexEnd = _components.size() - 1;

    std::swap(_components[indexDelete], _components[indexEnd]);

    EntityId EntityEnd = _indexToEntity[indexEnd];
    _entityToIndex[EntityEnd] = indexDelete;
    _indexToEntity[indexDelete] = EntityEnd;

    _entityToIndex.erase(id);
    _indexToEntity.erase(indexEnd);

    _components.pop_back();

}

template<typename T>
T &ComponentArray<T>::getData(EntityId id)
{
    Assert_Fatal_Error(_entityToIndex.find(id) != _entityToIndex.end(), "Retrieving non-existent component.");

    return &_components[_entityToIndex[id]];
}

template<typename T>
void ComponentArray<T>::EntityDestroyed(EntityId id)
{
    if (_indexToEntity.find(id) != _indexToEntity.end())
    {
        deleteData(id);
    }
}

#endif //QUACKENGINE_COMPONENTARRAY_HPP
