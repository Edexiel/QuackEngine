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
#include "fmt/core.h"


namespace reactphysics3d
{
    class PhysicsWorld;
}

//Serialization
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/access.hpp>

class World
{
private:
    struct EntityHandler
    {
        EntityHandler() = default;
        EntityHandler(Entity id, World *world) : id(id), world(world) {}

        Entity id;
        World* world;

        template<class Archive, class T>
        void save(Archive &archive, Entity &e, const char *name)
        {
            if (world->HasComponent<T>(e))
            {
                archive(cereal::make_nvp(name, world->GetComponent<T>(e)));
            }
        }

        template<class Archive>
        void serialize(Archive &archive)
        {
            archive(CEREAL_NVP(id));
            save<Archive, Component::Name>(archive, id, "Name");
            save<Archive, Component::Transform>(archive, id, "Transform");
//        save<Archive, Component::Camera>(archive, e,"Camera");
//        save<Archive,Component::Light>(archive, e,"Light");
//        save<Archive,Component::Model>(archive, e,"Model");
//        save<Archive,Component::RigidBody>(archive, e,"RigidBody");
        }
    };



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

///***************SERIALIZATION**************/////////
    friend class cereal::access;


    template<class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(_name));

        std::vector<EntityHandler> entities;
        for (Entity &entity : _entityManager->GetEntities())
            entities.emplace_back(entity, this);

        archive(CEREAL_NVP(entities));
        //serialize(archive, entity);
    }
};


#include "Scene/Core/World.inl"

#endif //QUACKENGINE_WORLD_HPP
