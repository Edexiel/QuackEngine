//
// Created by gnisi on 19/03/2021.
//

#ifndef QUACKENGINE_COMPONENTARRAY_HPP
#define QUACKENGINE_COMPONENTARRAY_HPP

#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Scene/Core/Entity.hpp"
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
    void AddData(EntityId id, T &data);

    void DeleteData(EntityId id);

    T &GetData(EntityId id);

    virtual void EntityDestroyed(EntityId id) override;

};

template<typename T>
void ComponentArray<T>::AddData(EntityId id, T &data)
{
    size_t end = _components.size();
    _components.emplace_back(std::move(data));
    (void)_entityToIndex.insert({id, end});
    (void)_indexToEntity.insert({end, id});
}

template<typename T>
void ComponentArray<T>::DeleteData(EntityId id)
{
    Assert_Fatal_Error(_entityToIndex.find(id) != _entityToIndex.end(), "Removing non-existent component.");

    size_t indexDelete = _entityToIndex[id];
    size_t indexEnd = _components.size() - 1;

    std::swap(_components[indexDelete], _components[indexEnd]);

    EntityId entityEnd = _indexToEntity[indexEnd];
    _entityToIndex[entityEnd] = indexDelete;
    _indexToEntity[indexDelete] = entityEnd;

    (void)_entityToIndex.erase(id);
    (void)_indexToEntity.erase(indexEnd);

    _components.pop_back();

}

template<typename T>
T &ComponentArray<T>::GetData(EntityId id)
{
    Assert_Fatal_Error(_entityToIndex.find(id) != _entityToIndex.end(), "Retrieving non-existent component.");

    return &_components[_indexToEntity[id]];
}

template<typename T>
void ComponentArray<T>::EntityDestroyed(EntityId id)
{
    if (_indexToEntity.find(id) != _indexToEntity.end()) {
        DeleteData(id);
    }
}

#endif //QUACKENGINE_COMPONENTARRAY_HPP
