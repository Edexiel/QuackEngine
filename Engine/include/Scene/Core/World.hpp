#ifndef QUACKENGINE_WORLD_HPP
#define QUACKENGINE_WORLD_HPP

#include <utility>
#include <string>

#include "Types.hpp"
#include "Scene/Core/EntityManager.hpp"
#include "Scene/Core/SystemManager.hpp"
#include "Scene/Core/ComponentManager.hpp"
#include "Physics/PhysicsEventManager.hpp"


//Serialization, yeah sorry
#include <cereal/types/string.hpp>
#include "Scene/Component/Camera.hpp"
#include "Scene/Component/Light.hpp"
#include "Scene/Component/Model.hpp"
#include "Scene/Component/RigidBody.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Component/Name.hpp"
#include "fmt/core.h"

//Serialization
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/access.hpp>
#include "Engine.hpp"


namespace reactphysics3d
{
    class PhysicsWorld;
}

class World
{
private:
    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<SystemManager> _systemManager;
    reactphysics3d::PhysicsWorld *_physicsWorld = nullptr;

    std::string _name;

public:
    World() = delete;
    explicit World(std::string &name);

    void Init();

    void Clear();

    // Entity methods
    Entity CreateEntity(std::string name) const;

    void DestroyEntity(Entity id);

    // Component methods
    template<typename T>
    void RegisterComponent();

    template<typename T>
    void AddComponent(Entity id, T component) const;

    template<typename T>
    void RemoveComponent(Entity id);

    template<typename T>
    T &GetComponent(Entity id) const;

    template<typename T>
    bool HasComponent(Entity id) const;

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

    const std::unique_ptr<SystemManager> &GetSystemManager() const;


    ///***************SERIALIZATION**************/////////
    friend class cereal::access;

    struct EntityHandler
    {
        EntityHandler() = default;

        explicit EntityHandler(Entity id, const World *world) : id(id), world(world)
        {}

        const World *world;
        Entity id;

        template<class Archive, class T>
        void write(Archive &archive, const Entity &e, const char *name) const
        {
            if (world->HasComponent<T>(e))
            {
                archive(cereal::make_nvp(name, world->GetComponent<T>(e)));
            }
        }

        template<class Archive, class T>
        void read(Archive &archive, T &component, const char *name) const
        {
            archive(cereal::make_nvp(name, component));
        }

        template<class Archive>
        void save(Archive &archive) const
        {
            archive(CEREAL_NVP(id));

            write<Archive, Component::Name>(archive, id, "Name");
            write<Archive, Component::Transform>(archive, id, "Transform");
            write<Archive, Component::Camera>(archive, id, "Camera");
            write<Archive, Component::Light>(archive, id, "Light");
            write<Archive, Component::Model>(archive, id, "Model");
//        save<Archive,Component::RigidBody>(archive, id,"RigidBody");
        }

        template<class Archive>
        void load(Archive &archive)
        {
            archive(CEREAL_NVP(id));
            World& w = Engine::Instance().GetCurrentWorld();
            Component::Name name;
            read<Archive, Component::Name>(archive, name, "Name");
            world->CreateEntity(name.name);

            Component::Transform t;
            Component::Camera c;
            Component::Light l;
            Component::Model m;

            read<Archive, Component::Transform>(archive, t, "Transform");
            read<Archive, Component::Camera>(archive, c, "Camera");
            read<Archive, Component::Light>(archive, l, "Light");
            read<Archive, Component::Model>(archive, m, "Model");


            //world->AddComponent(id, name.name);
        }

    };

    template<class Archive>
    void save(Archive &archive) const
    {
        archive(cereal::make_nvp("name", _name));

        std::vector<EntityHandler> entities;
        for (Entity &entity : _entityManager->GetEntities())
            entities.emplace_back(entity, this);

        archive(CEREAL_NVP(entities));
    }

    template<class Archive>
    void load(Archive &archive)
    {
        archive(_name);
        std::vector<EntityHandler> entities;
        archive(CEREAL_NVP(entities));
    }
};


#include "Scene/Core/World.inl"

#endif //QUACKENGINE_WORLD_HPP
