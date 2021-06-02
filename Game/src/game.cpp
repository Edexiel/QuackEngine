#include "game.hpp"

#include "Engine.hpp"
#include "Scene/Core/World.hpp"

#include "Scene/Component/Transform.hpp"
#include "Scene/Component/Animator.hpp"
#include "Scene/Component/RigidBody.hpp"
#include "Scene/Component/CharacterController.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Renderer/RendererInterface.hpp"

#include "Renderer/ProcessBase.hpp"
#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/System/CameraSystem.hpp"
#include "Scene/System/RenderSystem.hpp"
#include "Scene/System/LightSystem.hpp"
#include "Scene/System/AnimatorSystem.hpp"
#include "Scene/System/CharacterControllerSystem.hpp"


#include "Enemy/EnemyComponent.hpp"

#include "Player/Player.hpp"

using namespace Resources;
using namespace Renderer;

void Game::Init(Engine &engine)
{
    // Loading of scene "main"
    {
        World &main = engine.CreateWorld("Main");
        main.SetRegister(&Register);
        main.SetInitGame(&InitGame);
        main.SetInitSystems(&InitGame);
        main.SetInitSettings(&InitSettings);

        Register(main);
        InitSystems(main);

        engine.LoadWorld(main);
    }

    engine.SetCurrentWorld("Main"); //obligatoire
/** Exemple of adding a new scene **/

//    //Loading of scene "..."
//    {
//        World &main = engine.CreateWorld("...");
//        main.SetRegisterFunctionPtr(&Register...);
//        main.SetInitFunctionPtr(&Init...);
//        engine.LoadWorld(...);
//    }

/** You can select the active scene , default will be the first scene added **/

}

void Game::Register(World &world)
{
    Log_Info("Registering Comp/Sys for: {}", world.GetName());

    /** Register components **/

    world.RegisterComponent<Component::Name>();
    world.RegisterComponent<Component::Transform>();
    world.RegisterComponent<Component::Model>();
    world.RegisterComponent<Component::Camera>();
    world.RegisterComponent<Component::Light>();
    world.RegisterComponent<Component::RigidBody>();
    world.RegisterComponent<Component::CharacterController>();
    world.RegisterComponent<Component::Animator>();
    world.RegisterComponent<EnemyComponent>();
    world.RegisterComponent<PlayerComponent>();

    /** Register systems **/
    world.RegisterSystem<RenderSystem>();
    world.RegisterSystem<CameraSystem>();
    world.RegisterSystem<LightSystem>();
    world.RegisterSystem<PhysicsSystem>();
    world.RegisterSystem<CharacterControllerSystem>();
    world.RegisterSystem<AnimatorSystem>();
    world.RegisterSystem<PlayerSystem>();
    world.RegisterSystem<EnemyManagerSystem>();

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


}

void Game::InitGame(World &world)
{
    Log_Info("Initializing scene: {}", world.GetName());

    world.GetSystem<EnemyManagerSystem>()->GenerateEnemies(10, {0, 0, 0}, 50.f, 100.f);
}

void Game::InitSystems(World &world)
{
    Log_Info("Initializing systems: {}", world.GetName());

    /** Init Systems **/
    world.GetSystem<PhysicsSystem>()->Init();
    world.GetSystem<LightSystem>()->Update();

    /** Post process ? **/
    //NoteDisplayProcess* noteDisplayProcess = new NoteDisplayProcess();
//    std::unique_ptr <ProcessBase> ptr = std::make_unique<NoteDisplayProcess>(NoteDisplayProcess());
//    engine.GetPostProcessManager().AddProcess(ptr);
}

void Game::InitSettings(World &world)
{
    RendererPlatform::ClearColor({0.5f, 0.5f, 0.5f, 0.0f});
    Renderer::RendererPlatform::EnableDepthBuffer(true);
}
