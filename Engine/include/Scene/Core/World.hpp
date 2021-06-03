#ifndef QUACKENGINE_WORLD_HPP
#define QUACKENGINE_WORLD_HPP

#include <utility>
#include <string>
#include <map>

#include "Types.hpp"
#include "Scene/Core/EntityManager.hpp"
#include "Scene/Core/SystemManager.hpp"
#include "Scene/Core/ComponentManager.hpp"
#include "Physics/PhysicsEventManager.hpp"

#include "Scene/System/PhysicsSystem.hpp"

#include "Debug/Log.hpp"

//Serialization, yeah sorry
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/access.hpp>

#include "Scene/Component/Camera.hpp"
#include "Scene/Component/Light.hpp"
#include "Scene/Component/Model.hpp"
#include "Scene/Component/RigidBody.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Component/Name.hpp"
#include "Scene/Component/Animator.hpp"
#include "Scene/Component/CameraGameplay.hpp"
#include "Scene/Component/CharacterController.hpp"
#include "Scene/Component/ParticleEmitter.hpp"
#include "Scene/Component/SimpleShadow.hpp"

#include "Tools/Type.hpp"

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

    void Init(Engine &engine);

    void Clear();

    // Entity methods
    Entity CreateEntity(const std::string& name) const;

    Entity CreateEntity() const;

    void DestroyEntity(Entity id);

    // Component methods
    template<typename T>
    void RegisterComponent() const;

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
    T* RegisterSystem() const;

    template<typename T>
    void SetSystemSignature(Signature signature);

    reactphysics3d::PhysicsWorld *GetPhysicsWorld() const;

    const std::string &GetName() const;

    const std::unique_ptr<EntityManager> &GetEntityManager() const;

    //const std::unique_ptr<SystemManager> &GetSystemManager() const;

    template<class T>
    T* GetSystem();


    ///***************SERIALIZATION**************/////////
    friend class cereal::access;

    struct EntityHandler
    {
    private :

        template<class Archive, class T>
        void write(Archive &archive, Entity e, const std::string &name) const
        {
            if (components.at(name))
            {
                archive(cereal::make_nvp(name, world->GetComponent<T>(e)));
            }
        }

        template<class Archive, class T>
        void read(Archive &archive, World &w, Entity entity, const std::string &name) const
        {
            auto it = components.find(name);
            if (it == components.end())
                return;
            if (it->second)
            {
                T component;
                archive(cereal::make_nvp(name, component));
                //w.RegisterComponent<T>();
                w.AddComponent(entity, component);
            }
        }

        template<typename T>
        void build(const std::string &name)
        {
            components[name] = world->HasComponent<T>(id);
        }

    public :

        EntityHandler() = default;

        explicit EntityHandler(Entity id, const World *world) : id(id), world(world)
        {}

        const World *world = nullptr;
        Entity id{0};
        std::map<std::string, bool> components{};


        void BuildArray()
        {
            build<Component::Name>("Name");
            build<Component::Transform>("Transform");
            build<Component::Camera>("Camera");
            build<Component::Light>("Light");
            build<Component::Model>("Model");
            build<Component::Animator>("Animator");
            build<Component::RigidBody>("RigidBody");
            build<Component::CameraGameplay>("CameraGameplay");
            build<Component::CharacterController>("CharacterController");
            build<Component::ParticleEmitter>("ParticleEmitter");
            build<Component::SimpleShadow>("SimpleShadow");
        }

        template<class Archive>
        void save(Archive &archive) const
        {
            //archive(CEREAL_NVP(id));

            archive(CEREAL_NVP(components));
            write<Archive, Component::Name>(archive, id, "Name");
            write<Archive, Component::Transform>(archive, id, "Transform");
            write<Archive, Component::Camera>(archive, id, "Camera");
            write<Archive, Component::Light>(archive, id, "Light");
            write<Archive, Component::Model>(archive, id, "Model");
            write<Archive, Component::Animator>(archive, id, "Animator");
            write<Archive, Component::RigidBody>(archive, id, "RigidBody");
            write<Archive, Component::CameraGameplay>(archive, id, "CameraGameplay");
            write<Archive, Component::CharacterController>(archive, id, "CharacterController");
            write<Archive, Component::ParticleEmitter>(archive, id, "ParticleEmitter");
            write<Archive, Component::SimpleShadow>(archive, id, "SimpleShadow");
        }

        template<class Archive>
        void load(Archive &archive)
        {
            World &w = Engine::Instance().GetCurrentWorld();
            Entity e = w.CreateEntity();

            archive(CEREAL_NVP(components));

            read<Archive, Component::Name>(archive, w, e, "Name");
            read<Archive, Component::Transform>(archive, w, e, "Transform");
            read<Archive, Component::Camera>(archive, w, e, "Camera");
            read<Archive, Component::Light>(archive, w, e, "Light");
            read<Archive, Component::Model>(archive, w, e, "Model");
            read<Archive, Component::Animator>(archive, w, e, "Animator");
            read<Archive, Component::RigidBody>(archive, w, e, "RigidBody");
            read<Archive, Component::CameraGameplay>(archive, w, e, "CameraGameplay");
            read<Archive, Component::ParticleEmitter>(archive, w, e, "ParticleEmitter");
            read<Archive, Component::CharacterController>(archive, w, e, "CharacterController");
            read<Archive, Component::SimpleShadow>(archive, w, e, "SimpleShadow");
        }


    };

    template<class Archive>
    void save(Archive &archive) const
    {
        archive(cereal::make_nvp("name", _name));

        std::vector<EntityHandler> entities;
        for (Entity &entity : _entityManager->GetEntities())
            entities.emplace_back(entity, this);

        for (auto &item : entities)
            item.BuildArray();

        archive(CEREAL_NVP(entities));
    }

    template<class Archive>
    void load(Archive &archive)
    {
        archive(_name);
        std::vector<EntityHandler> entities;
        archive(CEREAL_NVP(entities));

        GetSystem<PhysicsSystem>()->Init();
    }
};


#include "Scene/Core/World.inl"

#endif //QUACKENGINE_WORLD_HPP
