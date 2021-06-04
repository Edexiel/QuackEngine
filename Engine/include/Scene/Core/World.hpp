#ifndef QUACKENGINE_WORLD_HPP
#define QUACKENGINE_WORLD_HPP

#include <utility>
#include <string>
#include <map>

#include "Types.hpp"
#include "Scene/Core/EntityManager.hpp"
#include "Scene/Core/SystemManager.hpp"
#include "Scene/Core/ComponentManager.hpp"

#include "Scene/Component/ComponentBase.hpp"


#include "Debug/Log.hpp"

//Serialization, yeah sorry
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>

#include "Tools/Type.hpp"

#include "Engine.hpp"

typedef void (*InitFn)(World &world);
typedef void (*LoadFn)(const World &w, cereal::JSONInputArchive &a, const std::map<std::string, bool> &c, Entity id);
typedef void (*SaveFn)(const World &w, cereal::JSONOutputArchive &a, const std::map<std::string, bool> &c, Entity id);
typedef void (*BuildFn)(const World &world, std::map<std::string, bool> &c, Entity id);


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

    InitFn InitSystemsPtr = nullptr;
    InitFn InitGamePtr = nullptr;
    InitFn RegisterPtr = nullptr;
    InitFn InitSettingsPtr = nullptr;
    SaveFn SavePtr = nullptr;
    LoadFn LoadPtr = nullptr;
    BuildFn BuildPtr = nullptr;

public:
    World() = delete;
    explicit World(std::string &name);

    void SetInitGame(InitFn ptr);
    void SetInitSystems(InitFn ptr);
    void SetInitSettings(InitFn ptr);
    void SetRegister(InitFn ptr);
    void SetSave(SaveFn ptr);
    void SetLoad(LoadFn ptr);
    void SetBuild(BuildFn ptr);

    void Register();
    void InitSystems();
    void InitGame();
    void InitSettings();

    void Build(std::map<std::string, bool> &c, Entity id) const;
    void Save(cereal::JSONOutputArchive &a, const std::map<std::string, bool> &c, Entity id) const;
    void Load(cereal::JSONInputArchive &a, const std::map<std::string, bool> &c, Entity id) const;
    void Clear();

    Entity CreateEntity(const std::string &name) const;
    Entity CreateEntity() const;
    void DestroyEntity(Entity id);

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
    template<typename T>
    T *RegisterSystem() const;
    template<typename T>
    void SetSystemSignature(Signature signature);
    reactphysics3d::PhysicsWorld *GetPhysicsWorld() const;
    const std::string &GetName() const;
    const std::unique_ptr<EntityManager> &GetEntityManager() const;

    template<class T>
    T *GetSystem();


    struct EntityHandler
    {
    private :
        template<class T>
        void write(cereal::JSONOutputArchive &archive, Entity e, const std::string &name) const
        {
            auto it = components.find(name);
            if (it == components.end())
                return;

            if (it->second)
                archive(cereal::make_nvp(name, world.GetComponent<T>(e)));

        }

        template<class T>
        void read(cereal::JSONInputArchive &archive, Entity entity, const std::string &name) const
        {
            auto it = components.find(name);
            if (it == components.end())
                return;
            if (it->second)
            {
                T component;
                archive(cereal::make_nvp(name, component));
                world.AddComponent(entity, component);
            }
        }

        template<typename T>
        void build(const std::string &name)
        {
            components[name] = world.HasComponent<T>(id);
        }

    public :

        EntityHandler():world{Engine::Instance().GetCurrentWorld()}{}

        explicit EntityHandler(Entity id, const World &world) : id{id}, world{world}
        {}

        const World &world;
        Entity id{0};
        std::map<std::string, bool> components{};

        void BuildArray();
        void save(cereal::JSONOutputArchive &archive) const;
        void load(cereal::JSONInputArchive &archive);
    };

    void save(cereal::JSONOutputArchive &archive) const;
    void load(cereal::JSONInputArchive &archive);
};


#include "Scene/Core/World.inl"

#endif //QUACKENGINE_WORLD_HPP
