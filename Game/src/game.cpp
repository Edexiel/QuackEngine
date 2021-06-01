#include "game.hpp"

#include <cstdio>
#include <Enemy/EnemyComponent.hpp>
#include <Scene/System/CharacterControllerSystem.hpp>
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

#include "Player/Player.hpp"

using namespace Resources;
using namespace Renderer;

void Game::Init(Engine &engine) const
{
    World &world = engine.CreateWorld("Main");
    world.Init(engine);

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

    world.RegisterSystem<RenderSystem>();
    world.RegisterSystem<CameraSystem>();
    world.RegisterSystem<LightSystem>();
    world.RegisterSystem<PhysicsSystem>();
    world.RegisterSystem<CharacterControllerSystem>();
    world.RegisterSystem<AnimatorSystem>();
    world.RegisterSystem<PlayerSystem>();
    world.RegisterSystem<EnemyManagerSystem>();

    engine.GetResourcesManager().Init();


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

    engine.LoadWorld(world);
    engine.GetResourcesManager().LoadFolder(R"(./Asset)");

    world.GetSystem<PhysicsSystem>()->Init();

    //NoteDisplayProcess* noteDisplayProcess = new NoteDisplayProcess();
    std::unique_ptr <ProcessBase> ptr = std::make_unique<NoteDisplayProcess>(NoteDisplayProcess());
    engine.GetPostProcessManager().AddProcess(ptr);

    world.GetSystem<EnemyManagerSystem>()->GenerateEnemies(10, {0, 0, 0}, 50.f, 100.f);


    RendererPlatform::ClearColor({0.5f, 0.5f, 0.5f, 0.0f});

    Renderer::RendererPlatform::EnableDepthBuffer(true);

}

void Game::Update(float deltaTime)
{
    printf("Update");
}