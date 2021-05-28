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
#include "Renderer/PostProcess/KernelPostProcess.hpp"


#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/System/CameraSystem.hpp"
#include "Scene/System/RenderSystem.hpp"
#include "Scene/System/LightSystem.hpp"
#include "Scene/System/CharacterControllerSystem.hpp"


#include "Scene/System/AnimatorSystem.hpp"
#include "Scene/Component/Animator.hpp"

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



    auto renderSystem = world.RegisterSystem<RenderSystem>();
    auto cameraSystem = world.RegisterSystem<CameraSystem>();
    auto lightSystem = world.RegisterSystem<LightSystem>();
    auto physicsSystem = world.RegisterSystem<PhysicsSystem>();
    auto characterControllerSystem = world.RegisterSystem<CharacterControllerSystem>();
    auto animatorSystem = world.RegisterSystem<AnimatorSystem>();

    auto noteDisplaySystem = world.RegisterSystem<EnemyManagerSystem>();


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

    engine.LoadWorld(world);
    engine.GetResourcesManager().LoadFolder(R"(./Asset)");
    physicsSystem->Init();
    characterControllerSystem->Init();


//    //NoteDisplayProcess* noteDisplayProcess = new NoteDisplayProcess();
//    std::unique_ptr<ProcessBase> ptr = std::make_unique<NoteDisplayProcess>(NoteDisplayProcess());
//
//    engine.GetPostProcessManager().AddProcess(ptr);
//
//    noteDisplaySystem->GenerateEnemies(10, {0,0,0}, 50.f, 100.f);


    RendererPlatform::ClearColor({0.5f, 0.5f, 0.5f, 0.0f});

    Renderer::RendererPlatform::EnableDepthBuffer(true);

}

void Game::Update(float deltaTime)
{
    printf("Update");
}


//{
//Entity CameraEntity = world.CreateEntity("Camera");
//
//Component::Camera camera(1280,
//                         720,
//                         1000, 0.01f, 45.f * 3.1415f / 180.f);
//
//Component::Transform cameraTrs;
//cameraTrs.position = {0, 0, -5};
//world.AddComponent(CameraEntity, camera);
//world.AddComponent(CameraEntity, cameraTrs);
//
//
//ResourcesManager &resourcesManager = Engine::Instance().GetResourcesManager();
//
//Component::Transform t = {Maths::Vector3f{0, -1, 0}, Maths::Vector3f::One() * 0.2f,
//                          Maths::Quaternion({0, 1, 0}, Pi<float>())};
//engine.GetResourcesManager().ReLoadModel(R"(../../Game/Asset/Model/Vampire.fbx)",
//Renderer::VertexType::V_SKELETAL);
//Renderer::ModelRenderer md = engine.GetResourcesManager().LoadModel(R"(../../Game/Asset/Model/Vampire.fbx)",
//                                                                    Renderer::VertexType::V_SKELETAL);
//
//Material material;
//
//material.ambient = {1, 1, 1};
//material.diffuse = {1, 1, 1};
//material.specular = {1, 1, 1};
//material.checkLight = true;
//material.colorTexture = engine.GetResourcesManager().LoadTexture(
//        R"(../../Game/Asset/Texture/Bartender.png)");
//
//material.hasSkeleton = true;
////material.normalMap = engine.GetResourcesManager().LoadTexture(R"(..\..\Game\Asset\Texture\Floor_N.jpg)");
//
//MaterialInterface materialInterface = resourcesManager.GenerateMaterial("AnimationMaterial", material);
//
//md.AddMaterial(materialInterface);
//
//Animation animation = engine.GetResourcesManager().LoadAnimation(R"(../../Game/Asset/Model/Vampire.fbx)");
//
//
//for (int x = 0; x < 1; x++)
//{
//for (int y = 0; y < 1; y++)
//{
//for (int z = 0; z < 1; z++)
//{
//t.position.x = 0;
////t.position.y = 50.f /*- (float)y * 2*/;
////t.position.z = 20.f /*+ (float)z * 2*/;
//
//Entity id = world.CreateEntity("Sphere");
//
//Component::RigidBody rb;
//
//
//Component::Model cmd{md};
//world.AddComponent(id, t);
//world.AddComponent(id, cmd);
////world.AddComponent(id, rb);
//
//Component::Animator animator(animation);
////animator.PlayAnimation(animation);
//world.AddComponent(id, animator);
//
///*physicsSystem->SetRigidBody(id);
//physicsSystem->SetType(id, BodyType::DYNAMIC);
//physicsSystem->AddSphereCollider(id, 1.5f);*/
//}
//}
//}
//
//material.hasSkeleton = false;
//
////Test triggerCollision
//Component::RigidBody rbTrigger;
//
//Component::Transform tTrigger = {Maths::Vector3f{0, -2.5f, 20}, {1, 1, 1}, Maths::Quaternion{}};
//Entity idTrigger = world.CreateEntity("TriggerBox");
//
//Component::Model cmcube{engine.GetResourcesManager().LoadModel(R"(../../Game/Asset/Model/Cube.fbx)",
//                                                               Renderer::VertexType::V_NORMALMAP)};
//world.AddComponent(idTrigger, tTrigger);
//world.AddComponent(idTrigger, cmcube);
//world.AddComponent(idTrigger, rbTrigger);
//
//physicsSystem->SetRigidBody(idTrigger);
//physicsSystem->SetType(idTrigger, BodyType::STATIC);
//physicsSystem->AddBoxCollider(idTrigger, {1, 1, 1});
//physicsSystem->SetIsTrigger(idTrigger, true);
//
////Test contactCollision
//Component::RigidBody rbContact;
//
//Component::Transform tContact = {Maths::Vector3f{0, -5.f, 20}, {1, 1, 1}, Maths::Quaternion{}};
//Entity idContact = world.CreateEntity("ContactBox");
//
//world.AddComponent(idContact, tContact);
//world.AddComponent(idContact, cmcube);
//world.AddComponent(idContact, rbContact);
//
//physicsSystem->SetRigidBody(idContact);
//physicsSystem->SetType(idContact, BodyType::STATIC);
//physicsSystem->AddBoxCollider(idContact, {1, 1, 1});
//
//Entity idFloor = world.CreateEntity("Floor");
//
//Maths::Vector3f scale{20, 0.25, 20};
//Component::Transform tFloor = {Maths::Vector3f{0, -5, 20}, scale, Maths::Quaternion{}};
//
//
//Component::RigidBody rbFloor;
//Renderer::ModelRenderer mdFloor = engine.GetResourcesManager().LoadModel(
//        R"(../../Game/Asset/Model/Cube.fbx)",
//        Renderer::VertexType::V_NORMALMAP);
//
//material.colorTexture = engine.GetResourcesManager().LoadTexture(R"(../../Game/Asset/Texture/Floor_C.jpg)");
//
//MaterialInterface materialInterface2 = resourcesManager.GenerateMaterial("mat2", material);
//
//mdFloor.AddMaterial(materialInterface2);
//Component::Model cmFloor{mdFloor};
//world.AddComponent(idFloor, tFloor);
//world.AddComponent(idFloor, cmFloor);
//world.AddComponent(idFloor, rbFloor);
//
//physicsSystem->SetRigidBody(idFloor);
//physicsSystem->SetType(idFloor, BodyType::STATIC);
//physicsSystem->AddBoxCollider(idFloor, scale);
//
//
//Entity lightID = world.CreateEntity("Light");
////Entity lightID2 = world.CreateEntity("Light");
////Entity lightID3 = world.CreateEntity("Light");
//
//Component::Light light;
//
//light.type = Component::Light_Type::L_POINT;
//light.ambient = {0.1f, 0.1f, 0.1f};
//light.diffuse = {1, 1, 1};
//light.specular = {1, 1, 1};
//light.constant = 1.0f;
//light.linear = 0.0014f;
//light.quadratic = 0.000007f;
//
//light.outerSpotAngle = 10.5;
//light.spotAngle = 8.5;
//
//
//Component::Transform tl1 = {Maths::Vector3f::One() * -10, Maths::Vector3f::One(), Maths::Quaternion{}};
//world.AddComponent(lightID, light);
//world.AddComponent(lightID, tl1);
//
///*light.type = Component::Light_Type::L_POINT;
//light.diffuse = {1, 1, 1};
//light.specular = {1, 1, 1};
//Transform tl2 = {Maths::Vector3f::One() * -100, Maths::Vector3f::One(), Maths::Quaternion{}};
//
//world.AddComponent(lightID2, light);
//world.AddComponent(lightID2, tl2);
//
//light.type = Component::Light_Type::L_DIRECTIONAL;
//light.diffuse = {0, 0, 1};
//light.specular = {0, 0, 1};
//
////Audio::Sound sound = world.GetSoundManager().CreateSound("../../../inactive.ogg", Audio::SoundType::S_MUSIC);
////sound.Play();
////sound.SetVolume(0.05f);
//
//Transform tl3 = {Maths::Vector3f::Zero(), Maths::Vector3f::One(), Maths::Quaternion{3.1415 / 2, 1, 0, 0}};
//
//world.AddComponent(lightID3, light);
//world.AddComponent(lightID3, tl3);*/
//}
