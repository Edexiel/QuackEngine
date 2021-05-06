
inline rp3d::PhysicsWorld *World::GetPhysicsWorld() const
{
    return _physicsWorld;
}

inline void World::Clear()
{
    //todo:
}

inline Entity World::CreateEntity(std::string name)
{
    Entity id = _entityManager->Create();
    AddComponent(id, Component::Name{std::move(name)});
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
inline void World::AddComponent(Entity id, T component) //todo: maybe pass by const ref
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

inline const std::string &World::GetName() const
{
    return _name;
}


inline const std::unique_ptr<EntityManager> &World::GetEntityManager() const
{
    return _entityManager;
}

inline const std::unique_ptr<SystemManager> &World::GetSystemManager() const
{
    return _systemManager;
}
