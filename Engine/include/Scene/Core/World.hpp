#ifndef QUACKENGINE_WORLD_HPP
#define QUACKENGINE_WORLD_HPP

#include "Types.hpp"

#include "Scene/Core/EntityManager.hpp"
#include "Scene/Core/SystemManager.hpp"
#include "Scene/Core/ComponentManager.hpp"
#include "reactphysics3d/reactphysics3d.h"
#include "Scene/Component/Name.hpp"

#include <string>

//Serialization
#include <cereal/types/string.hpp>
#include <cereal/access.hpp>

class World
{
private:
    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<SystemManager> _systemManager;
    rp3d::PhysicsWorld *_physicsWorld = nullptr;
    std::string _name;


public:
    World() = delete;
    explicit World(std::string &name);

    void Init();

    void Clear();

    // Entity methods
    Entity CreateEntity(std::string name);

    void DestroyEntity(Entity id);

    // Component methods
    template<typename T>
    void RegisterComponent();

    template<typename T>
    void AddComponent(Entity id, T component);

    template<typename T>
    void RemoveComponent(Entity id);

    template<typename T>
    T &GetComponent(Entity id);

    template<typename T>
    bool HasComponent(Entity id);

    template<typename T>
    ComponentType GetComponentType();

    // System methods
    template<typename T>
    std::shared_ptr<T> RegisterSystem();

    template<typename T>
    void SetSystemSignature(Signature signature);

    rp3d::PhysicsWorld *GetPhysicsWorld() const;

    const std::string &GetName() const;

    const std::unique_ptr<EntityManager> &GetEntityManager() const;

    const std::unique_ptr<SystemManager> &GetSystemManager() const;

    friend class cereal::access;

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(_name);

    }

};
#include "Scene/Core/World.inl"

#endif //QUACKENGINE_WORLD_HPP
