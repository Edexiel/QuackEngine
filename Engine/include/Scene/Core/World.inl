template<typename T>
inline void World::RegisterComponent()
{
    fmt::print(fg(fmt::color::forest_green),"[ECS] Register: {}\n", demangle(typeid(T).name()));
    _componentManager->RegisterComponent<T>();
}

template<typename T>
inline void World::AddComponent(Entity id, T component) const //todo: maybe pass by const ref
{
    fmt::print(fg(fmt::color::forest_green),"[ECS] Add Component: {}\n",demangle(typeid(T).name()));
    _componentManager->AddComponent<T>(id, component);

    auto signature = _entityManager->GetSignature(id);
    signature.set(_componentManager->GetComponentType<T>(), true);
    _entityManager->SetSignature(id, signature);

    _systemManager->EntitySignatureChanged(id, signature);
}

template<typename T>
inline void World::RemoveComponent(Entity id)
{
    fmt::print(fg(fmt::color::forest_green),"[ECS] Remove component: {} from {}\n",demangle(typeid(T).name()),id);

    _componentManager->RemoveComponent<T>(id);

    auto signature = _entityManager->GetSignature(id);
    signature.set(_componentManager->GetComponentType<T>(), false);

    _entityManager->SetSignature(id, signature);
    _systemManager->EntitySignatureChanged(id, signature);
}

template<typename T>
inline T &World::GetComponent(Entity id) const
{
    return _componentManager->GetComponent<T>(id);
}

template<typename T>
inline bool World::HasComponent(Entity id) const
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
    fmt::print(fg(fmt::color::forest_green),"[ECS] Register system: {}\n",demangle(typeid(T).name()));

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
