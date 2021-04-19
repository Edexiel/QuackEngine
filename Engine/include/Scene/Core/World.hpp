//
// Created by gnisi on 22/03/2021.
//

#ifndef QUACKENGINE_WORLD_HPP
#define QUACKENGINE_WORLD_HPP

#include <utility>

#include "Types.hpp"
#include "Scene/Core/EntityManager.hpp"
#include "Scene/Core/SystemManager.hpp"
#include "Scene/Core/ComponentManager.hpp"
#include "Scene/Component/Name.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Audio/SoundManager.hpp"
#include "Renderer/RendererInterface.hpp"
#include "reactphysics3d/reactphysics3d.h"

#include "Input/PlatformInput.hpp"
#include "Input/InputManager.hpp"


class World
{
private:
    World() = default;

    static World _instance;

    Resources::ResourcesManager _resourcesManager;
    Audio::SoundManager _soundManager;
    Renderer::RendererInterface _rendererInterface;


    rp3d::PhysicsWorld *_physicsWorld;
    std::unique_ptr<ComponentManager> _componentManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<SystemManager> _systemManager;
    std::unique_ptr<rp3d::PhysicsCommon> _physicsManager;
    std::unique_ptr<Input::InputManager> _inputManager;


public:
    std::unique_ptr<Input::InputManager> &GetInputManager();

    static World &Instance();

    void Init(Input::PlatformInput &platformInput);

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

    const std::unique_ptr<rp3d::PhysicsCommon> &GetPhysicsManager() const;

    Resources::ResourcesManager &GetResourcesManager();

    Audio::SoundManager &GetSoundManager();

    Renderer::RendererInterface &GetRendererInterface();
    const std::unique_ptr<EntityManager> &GetEntityManager() const;
};

inline World World::_instance = World();

inline World &World::Instance()
{
    return _instance;
}

inline void World::Init(Input::PlatformInput &platformInput)
{
    _componentManager = std::make_unique<ComponentManager>();
    _entityManager = std::make_unique<EntityManager>();
    _systemManager = std::make_unique<SystemManager>();
    _physicsManager = std::make_unique<rp3d::PhysicsCommon>();

    _physicsWorld = _physicsManager->createPhysicsWorld();

    _soundManager.Init();

    _inputManager = std::make_unique<Input::InputManager>(platformInput);

    _componentManager->RegisterComponent<Name>();
}

inline rp3d::PhysicsWorld *World::GetPhysicsWorld() const
{
    return _physicsWorld;
}

inline const std::unique_ptr<rp3d::PhysicsCommon> &World::GetPhysicsManager() const
{
    return _physicsManager;
}

inline void World::Clear()
{

}

inline Entity World::CreateEntity(std::string name)
{
    Entity id = _entityManager->Create();
    AddComponent(id, Name{std::move(name)});
    return id;
}

inline void World::DestroyEntity(Entity id)
{
    _entityManager->Destroy(id);
    _componentManager->EntityDestroyed(id);
    _systemManager->EntityDestroyed(id);
}

template<typename T>
inline void World::RegisterComponent()
{
    _componentManager->RegisterComponent<T>();
}

template<typename T>
inline void World::AddComponent(Entity id, T component)
{
    _componentManager->AddComponent<T>(id, component);

    auto signature = _entityManager->GetSignature(id);
    signature.set(_componentManager->GetComponentType<T>(), true);
    _entityManager->SetSignature(id, signature);

    _systemManager->EntitySignatureChanged(id, signature);
}

template<typename T>
inline void World::RemoveComponent(Entity id)
{
    _componentManager->RemoveComponent<T>(id);

    auto signature = _entityManager->GetSignature(id);
    signature.set(_componentManager->GetComponentType<T>(), false);

    _entityManager->SetSignature(id, signature);
    _systemManager->EntitySignatureChanged(id, signature);
}

template<typename T>
inline T &World::GetComponent(Entity id)
{
    return _componentManager->GetComponent<T>(id);
}

template<typename T>
inline bool World::HasComponent(Entity id)
{
    return _componentManager->HasComponent<T>(id);
}

template<typename T>
inline ComponentType World::GetComponentType()
{
    return _componentManager->GetComponentType<T>();
}

template<typename T>
inline std::shared_ptr<T> World::RegisterSystem()
{
    return _systemManager->RegisterSystem<T>();
}

template<typename T>
inline void World::SetSystemSignature(Signature signature)
{
    _systemManager->SetSignature<T>(signature);
}

inline Resources::ResourcesManager &World::GetResourcesManager()
{
    return _resourcesManager;
}

inline Audio::SoundManager &World::GetSoundManager()
{
    return _soundManager;
}

inline Renderer::RendererInterface &World::GetRendererInterface()
{
    return _rendererInterface;
}

inline std::unique_ptr<Input::InputManager> &World::GetInputManager()
{
    return _inputManager;
}

inline const std::unique_ptr<EntityManager> &World::GetEntityManager() const
{
    return _entityManager;
}

#endif //QUACKENGINE_WORLD_HPP
