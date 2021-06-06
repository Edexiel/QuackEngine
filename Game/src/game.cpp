#include "game.hpp"

#include <cstdio>
#include <Enemy/EnemyComponent.hpp>
#include <Scene/System/CharacterControllerSystem.hpp>
#include <Renderer/UI/Text.hpp>
#include "Engine.hpp"
#include "Scene/Core/World.hpp"

#include "Scene/Component/EngineComponents.hpp"
#include "Scene/System/EngineSystems.hpp"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/RendererInterface.hpp"

#include "Renderer/ProcessBase.hpp"
#include "Renderer/PostProcess/KernelPostProcess.hpp"


#include "Enemy/EnemyComponent.hpp"
#include "Player/PlayerComponent.hpp"
#include "Player/PlayerSystem.hpp"

#include <cereal/archives/json.hpp>

using namespace Resources;
using namespace Renderer;

void Game::Init(Engine &engine)
{
    {

        World &main = engine.CreateWorld("Main");
        main.SetRegister(&Register);
        main.SetInitGame(&InitGame);
        main.SetInitSystems(&InitSystems);
        main.SetInitSettings(&InitSettings);

        /*** Serialization of external components**/
        main.SetLoad(&Load);
        main.SetSave(&Save);
        main.SetBuild(&Build);
        /*****************************************/

        engine.LoadWorld(main);
    }
    {
        World &main = engine.CreateWorld("Main2");
        main.SetRegister(&Register);
        main.SetInitGame(&InitGame);
        main.SetInitSystems(&InitSystems);
        main.SetInitSettings(&InitSettings);

        /*** Serialization of external components**/
        main.SetLoad(&Load);
        main.SetSave(&Save);
        main.SetBuild(&Build);
        /*****************************************/

    }
    {
        World &main = engine.CreateWorld("Main3");
        main.SetRegister(&Register);
        main.SetInitGame(&InitGame);
        main.SetInitSystems(&InitSystems);
        main.SetInitSettings(&InitSettings);

        /*** Serialization of external components**/
        main.SetLoad(&Load);
        main.SetSave(&Save);
        main.SetBuild(&Build);
        /*****************************************/
        //engine.LoadWorld(main);

    }
    //Village
    {
        World &main = engine.CreateWorld("Village");
        main.SetRegister(&Register);
        main.SetInitGame(&InitGame);
        main.SetInitSystems(&InitSystems);
        main.SetInitSettings(&InitSettings);

        /*** Serialization of external components**/
        main.SetLoad(&Load);
        main.SetSave(&Save);
        main.SetBuild(&Build);
        /*****************************************/


    }

    engine.SetCurrentWorld("Main"); //obligatoire
}

void Game::Register(World &world)
{
    Log_Info("Registering Component and Systems for: {}", world.GetName());

    /** Register components **/
    //global
    world.RegisterComponent<Component::Name>();
    world.RegisterComponent<Component::Transform>();
    world.RegisterComponent<Component::Model>();
    world.RegisterComponent<Component::Camera>();
    world.RegisterComponent<Component::Light>();
    world.RegisterComponent<Component::RigidBody>();
    world.RegisterComponent<Component::CharacterController>();
    world.RegisterComponent<Component::Animator>();
    world.RegisterComponent<Component::SimpleShadow>();
    world.RegisterComponent<Component::CameraGameplay>();
    world.RegisterComponent<Component::ParticleEmitter>();
    //local
    world.RegisterComponent<EnemyComponent>();
    world.RegisterComponent<PlayerComponent>();

    /** Register systems **/
    world.RegisterSystem<RenderSystem>();
    world.RegisterSystem<CameraSystem>();
    world.RegisterSystem<LightSystem>();
    world.RegisterSystem<PhysicsSystem>();
    world.RegisterSystem<CharacterControllerSystem>();
    world.RegisterSystem<CameraGameplaySystem>();
    world.RegisterSystem<AnimatorSystem>();
    world.RegisterSystem<PlayerSystem>();
    world.RegisterSystem<EnemyManagerSystem>();
    world.RegisterSystem<ParticleSystem>();
    world.RegisterSystem<SimpleShadowSystem>();


    /** Set signature of systems **/
    //Signature Renderer
    {
        Signature signatureRender;
        signatureRender.set(world.GetComponentType<Component::Model>());
        signatureRender.set(world.GetComponentType<Component::Transform>());
        world.SetSystemSignature<RenderSystem>(signatureRender);
    }
    //Signature Camera
    {
        Signature signatureCamera;
        signatureCamera.set(world.GetComponentType<Component::Camera>());
        signatureCamera.set(world.GetComponentType<Component::Transform>());
        world.SetSystemSignature<CameraSystem>(signatureCamera);
    }
    //Signature Light
    {
        Signature signatureLight;
        signatureLight.set(world.GetComponentType<Component::Light>());
        signatureLight.set(world.GetComponentType<Component::Transform>());
        world.SetSystemSignature<LightSystem>(signatureLight);
    }
    //Signature CharacterController
    {
        Signature signatureCharacterController;
        signatureCharacterController.set(world.GetComponentType<Component::Transform>());
        signatureCharacterController.set(world.GetComponentType<Component::RigidBody>());
        signatureCharacterController.set(world.GetComponentType<Component::CharacterController>());
        world.SetSystemSignature<CharacterControllerSystem>(signatureCharacterController);
    }
    //Signature CameraGameplay
    {
        Signature signatureCameraGameplay;
        signatureCameraGameplay.set(world.GetComponentType<Component::Transform>());
        signatureCameraGameplay.set(world.GetComponentType<Component::Camera>());
        signatureCameraGameplay.set(world.GetComponentType<Component::CameraGameplay>());
        world.SetSystemSignature<CameraGameplaySystem>(signatureCameraGameplay);
    }
    //Signature Physics
    {
        Signature signaturePhysics;
        signaturePhysics.set(world.GetComponentType<Component::Transform>());
        signaturePhysics.set(world.GetComponentType<Component::RigidBody>());
        world.SetSystemSignature<PhysicsSystem>(signaturePhysics);
    }
    //signature Animation
    {
        Signature signatureAnimation;
        signatureAnimation.set(world.GetComponentType<Component::Animator>());
        world.SetSystemSignature<AnimatorSystem>(signatureAnimation);
    }
    //signature enemymanager
    {
        Signature signatureEnemy;
        signatureEnemy.set(world.GetComponentType<EnemyComponent>());
        signatureEnemy.set(world.GetComponentType<Component::Transform>());
        world.SetSystemSignature<EnemyManagerSystem>(signatureEnemy);
    }
    //signature player
    {
        Signature signaturePlayer;
        signaturePlayer.set(world.GetComponentType<PlayerComponent>());
        signaturePlayer.set(world.GetComponentType<Component::Transform>());
        signaturePlayer.set(world.GetComponentType<Component::RigidBody>());
        signaturePlayer.set(world.GetComponentType<Component::CharacterController>());
        world.SetSystemSignature<PlayerSystem>(signaturePlayer);
    }

    //Signature particle
    {
        Signature signatureParticle;
        signatureParticle.set(world.GetComponentType<Component::Transform>());
        signatureParticle.set(world.GetComponentType<Component::ParticleEmitter>());
        world.SetSystemSignature<ParticleSystem>(signatureParticle);
    }
    //Signature Shadow
    {
        Signature signatureShadow;
        signatureShadow.set(world.GetComponentType<Component::Transform>());
        signatureShadow.set(world.GetComponentType<Component::SimpleShadow>());
        world.SetSystemSignature<SimpleShadowSystem>(signatureShadow);
    }


}

void Game::InitGame(World &world)
{
    Log_Info("Initializing scene: {}", world.GetName());
    //Engine::Instance().GetTimeManager().SetTime(1);
    //world.GetSystem<EnemyManagerSystem>()->GenerateEnemies(10, {0, 0, 0}, 50.f, 100.f);
}

void Game::InitSystems(World &world)
{
    Log_Info("Initializing systems: {}", world.GetName());

    Engine& engine = Engine::Instance();

    /** Init Systems **/
    world.GetSystem<PhysicsSystem>()->Init();
    world.GetSystem<LightSystem>()->Update();

    /** Post process ? **/
    std::unique_ptr<ProcessBase> ptr = std::make_unique<NoteDisplayProcess>(NoteDisplayProcess());
    engine.GetPostProcessManager().AddProcess(ptr);

    engine.GetPostProcessManager().AddProcess(new ParticleProcess());
    engine.GetPostProcessManager().AddProcess(new SimpleShadowProcess());

    std::unique_ptr<ProcessBase> ptr2 = std::make_unique<Renderer::Text>(Text("FontTest"));
    engine.GetPostProcessManager().AddProcess(ptr2);
}

void Game::InitSettings(World &world)
{
    RendererPlatform::ClearColor({0.5f, 0.5f, 0.5f, 0.0f});
}

template<typename T>
void build(const World &w, std::map<std::string, bool> &c, Entity e, const std::string &n)
{
    c[n] = w.HasComponent<T>(e);
}

template<class T>
void write(const World &w, cereal::JSONOutputArchive &a, Entity e, const std::map<std::string, bool> &c,
           const std::string &n)
{
    auto it = c.find(n);
    if (it == c.end())
        return;

    if (it->second)
    {
        a(cereal::make_nvp(n, w.GetComponent<T>(e)));
    }
}


template<class T>
void read(const World &w, cereal::JSONInputArchive &a, Entity e, const std::map<std::string, bool> &c,
          const std::string &n)
{
    auto it = c.find(n);
    if (it == c.end())
        return;
    if (it->second)
    {
        T component;
        a(cereal::make_nvp(n, component));
        w.AddComponent(e, component);
    }
}

void Game::Save(const World &w, cereal::JSONOutputArchive &a, const std::map<std::string, bool> &c, Entity e)
{
    write<PlayerComponent>(w, a, e, c, "Player");
}

void Game::Load(const World &w, cereal::JSONInputArchive &a, const std::map<std::string, bool> &c, Entity e)
{
    read<PlayerComponent>(w, a, e, c, "Player");
}

void Game::Build(const World &world, std::map<std::string, bool> &c, Entity id)
{
    build<PlayerComponent>(world, c, id, "Player");
}
