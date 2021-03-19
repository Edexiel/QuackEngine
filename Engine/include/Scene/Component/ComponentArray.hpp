//
// Created by gnisi on 19/03/2021.
//

#ifndef QUACKENGINE_COMPONENTARRAY_HPP
#define QUACKENGINE_COMPONENTARRAY_HPP

#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Scene/Entity/Entity.hpp"

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
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
    T *getData(EntityId id);
};

template<typename T>
void ComponentArray<T>::addData(EntityId id, T &data)
{
    size_t end = _components.size();
    _components.push_back(data);
    _entityToIndex.insert({id, end});
    _indexToEntity.insert({end, id});
}

template<typename T>
void ComponentArray<T>::deleteData(EntityId id)
{
    auto it = _entityToIndex.find(id);
    if (it != _entityToIndex.end())
    {
        size_t indexDelete = _components[it->second];
        size_t indexEnd = _components.size() - 1;

        std::swap(_components[indexDelete], _components[indexEnd]);

        EntityId EntityEnd = _indexToEntity[indexEnd];
        _entityToIndex[EntityEnd]=indexDelete;
        _indexToEntity[indexDelete] = EntityEnd;

        _entityToIndex.erase(id);
        _indexToEntity.erase(indexEnd);

        _components.pop_back();
    }
}

template<typename T>
T *ComponentArray<T>::getData(EntityId id)
{
    auto it = _entityToIndex.find(id);
    if (it != _entityToIndex.end())
    {
        return &_components[it->second];
    }
    return nullptr;
}

#endif //QUACKENGINE_COMPONENTARRAY_HPP
