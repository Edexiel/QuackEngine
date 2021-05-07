#ifndef QUACKENGINE_WORLD_HPP
#define QUACKENGINE_WORLD_HPP

#include <utility>

#include "Types.hpp"

#include "Scene/Core/EntityManager.hpp"
#include "Scene/Core/SystemManager.hpp"
#include "Scene/Core/ComponentManager.hpp"
#include "Physics/PhysicsEventManager.hpp"

#include <string>


//Serialization, yeah sorry
#include <cereal/types/string.hpp>
#include "Scene/Component/Camera.hpp"
#include "Scene/Component/Light.hpp"
#include "Scene/Component/Model.hpp"
#include "Scene/Component/RigidBody.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Component/Name.hpp"


namespace reactphysics3d
{
    class PhysicsWorld;
}

//Serialization
#include <cereal/types/string.hpp>
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

    reactphysics3d::PhysicsWorld *GetPhysicsWorld() const;

    const std::string &GetName() const;

    const std::unique_ptr<EntityManager> &GetEntityManager() const;


    friend class cereal::access;

    template<class Archive, class T>
    void save(Archive &archive, Entity &e)
    {
        if (HasComponent<T>(e))
        {
            archive(GetComponent<T>(e));
        }
    }

    template<class Archive>
    void serialize(Archive &archive,
                   Entity &e)
    {
        save<Component::Name>(archive, e);
        save<Component::Transform>(archive, e);
        save<Component::Camera>(archive, e);
        save<Component::Light>(archive, e);
        save<Component::Model>(archive, e);
        save<Component::RigidBody>(archive, e);
    }


    template<class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(_name));

        for (const Entity &entity : _entityManager->GetEntities())
        {
            archive(reinterpret_cast<Entity>(entity));
        }

    }
};

#include "Scene/Core/World.inl"

#endif //QUACKENGINE_WORLD_HPP
