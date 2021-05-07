#ifndef QUACKENGINE_WORLD_HPP
#define QUACKENGINE_WORLD_HPP

#include <utility>

#include "Types.hpp"

#include "Scene/Core/EntityManager.hpp"
#include "Scene/Core/SystemManager.hpp"
#include "Scene/Core/ComponentManager.hpp"
#include "Physics/PhysicsEventManager.hpp"

#include "Scene/Component/Name.hpp"
#include <string_view>

namespace reactphysics3d
{
    class PhysicsWorld;
}

//Serialization
#include <cereal/types/string_view.hpp>
#include <cereal/access.hpp>

class World
{
private:
    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<SystemManager> _systemManager;
public:
    const std::unique_ptr<SystemManager> &GetSystemManager() const;
private:

    reactphysics3d::PhysicsWorld *_physicsWorld = nullptr;

    std::string_view _name;


public:
    World() = delete;
    explicit World(std::string_view &name);

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

    reactphysics3d::PhysicsWorld *GetPhysicsWorld() const;

    const std::string_view &GetName() const;

    const std::unique_ptr<EntityManager> &GetEntityManager() const;


    friend class cereal::access;

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(_name);

    }
};
#include "Scene/Core/World.inl"

#endif //QUACKENGINE_WORLD_HPP
