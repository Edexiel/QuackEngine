#include <cstdio>
#include <Scene/System/CharacterControllerSystem.hpp>
#include "Engine.hpp"

#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Component/RigidBody.hpp"
#include "Scene/Component/CharacterController.hpp"
#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/System/CameraSystem.hpp"
#include "Scene/System/CharacterControllerSystem.hpp"

#include "Resources/ResourcesManager.hpp"

#include "Renderer/RendererPlatform.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Renderer/Material.hpp"
#include "Renderer/Shape.hpp"
#include "game.hpp"

#include "Renderer/ProcessBase.hpp"
#include "Renderer/PostProcess/KernelPostProcess.hpp"

#include "Scene/Component/Animator.hpp"

#include "Thread/ThreadPool.hpp"

#include "reactphysics3d/reactphysics3d.h"

using namespace Component;
using namespace Resources;
using namespace Renderer;

void doStuff(int i)
{
    std::cout << "try " << i << std::endl;
}

void Game::Init()
{
    printf("T_INIT");


    World &world = Engine::Instance().CreateWorld("Main");
    world.Init();

    //Register
    {
        world.RegisterComponent<Name>();
        world.RegisterComponent<Transform>();
        world.RegisterComponent<Model>();
        world.RegisterComponent<Camera>();
        world.RegisterComponent<Light>();
        world.RegisterComponent<RigidBody>();
        world.RegisterComponent<Animator>();
        world.RegisterComponent<CharacterController>();
    }

    auto renderSystem = world.RegisterSystem<RenderSystem>();
    auto cameraSystem = world.RegisterSystem<CameraSystem>();
    auto lightSystem = world.RegisterSystem<LightSystem>();
    auto physicsSystem = world.RegisterSystem<PhysicsSystem>();
    auto characterControllerSystem = world.RegisterSystem<CharacterControllerSystem>();

    Engine &engine = Engine::Instance();

    engine.GetRendererInterface().Set(renderSystem, cameraSystem, lightSystem);
    engine.GetResourcesManager().Init();
    engine.GetResourcesManager().LoadFolder(R"(..\..\Game\Asset\)");

    //Signature Renderer
    {
        Signature signatureRender;
        signatureRender.set(world.GetComponentType<Component::Model>());
        signatureRender.set(world.GetComponentType<Transform>());
        world.SetSystemSignature<RenderSystem>(signatureRender);
    }

    //Signature Camera
    {
        Signature signatureCamera;
        signatureCamera.set(world.GetComponentType<Component::Camera>());
        signatureCamera.set(world.GetComponentType<Transform>());
        world.SetSystemSignature<CameraSystem>(signatureCamera);
    }

    //Signature Light
    {
        Signature signatureLight;
        signatureLight.set(world.GetComponentType<Component::Light>());
        signatureLight.set(world.GetComponentType<Transform>());
        world.SetSystemSignature<LightSystem>(signatureLight);
    }
    //Signature CharacterController
    {
        Signature signatureCharacterController;
        signatureCharacterController.set(world.GetComponentType<Transform>());
        signatureCharacterController.set(world.GetComponentType<RigidBody>());
        signatureCharacterController.set(world.GetComponentType<CharacterController>());
        world.SetSystemSignature<CharacterControllerSystem>(signatureCharacterController);
    }
    //Signature Physics
    {
        Signature signaturePhysics;
        signaturePhysics.set(world.GetComponentType<Transform>());
        signaturePhysics.set(world.GetComponentType<Component::RigidBody>());
        world.SetSystemSignature<PhysicsSystem>(signaturePhysics);
    }

    physicsSystem->Init();
    characterControllerSystem->Init();


    {
        Entity CameraEntity = world.CreateEntity("Camera");

        Component::Camera camera(1280,
                                 720,
                                 1000, 0.01f, 45.f * 3.1415f / 180.f);

        Transform cameraTrs;
        cameraTrs.position = {0, 0, -5};
        world.AddComponent(CameraEntity, camera);
        world.AddComponent(CameraEntity, cameraTrs);

    }
    ResourcesManager &resourcesManager = Engine::Instance().GetResourcesManager();

    Transform t = {Maths::Vector3f{0, -1, 0}, Maths::Vector3f::One() * 0.2f, Maths::Quaternion({0,1,0}, Pi<float>())};
    engine.GetResourcesManager().ReLoadModel(R"(..\..\Game\Asset\Model\Vampire.fbx)", Renderer::VertexType::V_SKELETAL);
    Component::Model md = engine.GetResourcesManager().LoadModel(R"(..\..\Game\Asset\Model\Vampire.fbx)", Renderer::VertexType::V_SKELETAL);

    Material material;

    material.ambient = {1, 1, 1};
    material.diffuse = {1, 1, 1};
    material.specular = {1, 1, 1};
    material.checkLight = true;
    material.colorTexture = engine.GetResourcesManager().LoadTexture(R"(..\..\Game\Asset\Texture\Bartender.png)");

    material.hasSkeleton = true;
    //material.normalMap = engine.GetResourcesManager().LoadTexture(R"(..\..\Game\Asset\Texture\Floor_N.jpg)");

    MaterialInterface materialInterface = resourcesManager.GenerateMaterial("AnimationMaterial", material);

    md.AddMaterial(materialInterface);

    Animation animation = engine.GetResourcesManager().LoadAnimation(R"(..\..\Game\Asset\Model\Vampire.fbx)");


    for (int x = 0; x < 1; x++)
    {
        for (int y = 0; y < 1; y++)
        {
            for (int z = 0; z < 1; z++)
            {
                t.position.x = 0;
                //t.position.y = 50.f /*- (float)y * 2*/;
                //t.position.z = 20.f /*+ (float)z * 2*/;

                Entity id = world.CreateEntity("Sphere");

                Component::RigidBody rb;


                world.AddComponent(id, t);
                world.AddComponent(id, md);
                //world.AddComponent(id, rb);

                Component::Animator animator(animation);
                //animator.PlayAnimation(animation);
                world.AddComponent(id, animator);

                /*physicsSystem->SetRigidBody(id);
                physicsSystem->SetType(id, BodyType::DYNAMIC);
                physicsSystem->AddSphereCollider(id, 1.5f);*/

            }
        }
    }

    material.hasSkeleton = false;

//Test triggerCollision
    Component::RigidBody rbTrigger;
    Component::Model mdTrigger = engine.GetResourcesManager().LoadModel(R"(../../Game/Asset/Model/Cube.fbx)", Renderer::VertexType::V_NORMALMAP);
    Transform tTrigger = {Maths::Vector3f{0, -2.5f, 20}, {1,1,1}, Maths::Quaternion{}};
    Entity idTrigger = world.CreateEntity("TriggerBox");

    world.AddComponent(idTrigger, tTrigger);
    world.AddComponent(idTrigger, mdTrigger);
    world.AddComponent(idTrigger, rbTrigger);

    PhysicsSystem::SetRigidBody(idTrigger);
    PhysicsSystem::SetType(idTrigger, BodyType::STATIC);
    PhysicsSystem::AddBoxCollider(idTrigger,{1,1,1});
//    PhysicsSystem::SetIsTrigger(idTrigger, true);

//Test contactCollision
    Component::RigidBody rbContact;
    Component::Model mdContact = engine.GetResourcesManager().LoadModel(R"(../../Game/Asset/Model/Cube.fbx)", Renderer::VertexType::V_NORMALMAP);
    Transform tContact = {Maths::Vector3f{2.5f, -2.5f, 20}, {1,1,1}, Maths::Quaternion{}};
    CharacterController characterController;
    characterController.speed = 5.f;
    Entity idContact = world.CreateEntity("ContactBox");

    world.AddComponent(idContact, tContact);
    world.AddComponent(idContact, mdContact);
    world.AddComponent(idContact, rbContact);
    world.AddComponent(idContact, characterController);

    PhysicsSystem::SetRigidBody(idContact);
    PhysicsSystem::SetType(idContact, BodyType::STATIC);
    PhysicsSystem::AddBoxCollider(idContact,{1,1,1});

    Entity idFloor = world.CreateEntity("Floor");

    Maths::Vector3f scale{20, 0.25, 20};
    Transform tFloor = {Maths::Vector3f{0, -5, 20}, scale, Maths::Quaternion{}};


    Component::RigidBody rbFloor;
    Component::Model mdFloor = engine.GetResourcesManager().LoadModel(R"(../../Game/Asset/Model/Cube.fbx)",
                                                                      Renderer::VertexType::V_NORMALMAP);

    material.colorTexture = engine.GetResourcesManager().LoadTexture(R"(../../Game/Asset/Texture/Floor_C.jpg)");

    MaterialInterface materialInterface2 = resourcesManager.GenerateMaterial("mat2", material);

    mdFloor.AddMaterial(materialInterface2);

    world.AddComponent(idFloor, tFloor);
    world.AddComponent(idFloor, mdFloor);
    world.AddComponent(idFloor, rbFloor);

    PhysicsSystem::SetRigidBody(idFloor);
    PhysicsSystem::SetType(idFloor, BodyType::STATIC);
    PhysicsSystem::AddBoxCollider(idFloor, scale);


    Entity lightID = world.CreateEntity("Light");
    //Entity lightID2 = world.CreateEntity("Light");
    //Entity lightID3 = world.CreateEntity("Light");

    Component::Light light;

    light.type = Component::Light_Type::L_POINT;
    light.ambient = {0.1f, 0.1f, 0.1f};
    light.diffuse = {1, 1, 1};
    light.specular = {1, 1, 1};
    light.constant = 1.0f;
    light.linear = 0.0014f;
    light.quadratic = 0.000007f;

    light.outerSpotAngle = 10.5;
    light.spotAngle = 8.5;


    Transform tl1 = {Maths::Vector3f::One() * -10, Maths::Vector3f::One(), Maths::Quaternion{}};
    world.AddComponent(lightID, light);
    world.AddComponent(lightID, tl1);

    /*light.type = Component::Light_Type::L_POINT;
    light.diffuse = {1, 1, 1};
    light.specular = {1, 1, 1};
    Transform tl2 = {Maths::Vector3f::One() * -100, Maths::Vector3f::One(), Maths::Quaternion{}};

    world.AddComponent(lightID2, light);
    world.AddComponent(lightID2, tl2);

    light.type = Component::Light_Type::L_DIRECTIONAL;
    light.diffuse = {0, 0, 1};
    light.specular = {0, 0, 1};

    //Audio::Sound sound = world.GetSoundManager().CreateSound("../../../inactive.ogg", Audio::SoundType::S_MUSIC);
    //sound.Play();
    //sound.SetVolume(0.05f);

    Transform tl3 = {Maths::Vector3f::Zero(), Maths::Vector3f::One(), Maths::Quaternion{3.1415 / 2, 1, 0, 0}};

    world.AddComponent(lightID3, light);
    world.AddComponent(lightID3, tl3);*/

    Renderer::RendererPlatform::EnableDepthBuffer(true);

    Renderer::KernelPostProcess* kP = new Renderer::KernelPostProcess("Kernel 1");

    kP->offset = 1.0f/300;
    kP->array[0] = 0;
    kP->array[1] = 1;
    kP->array[2] = 0;
    kP->array[3] = 1;
    kP->array[4] = -4;
    kP->array[5] = 1;
    kP->array[6] = 0;
    kP->array[7] = 1;
    kP->array[8] = 0;

    //Thread::Task<int>* tsk = new Thread::Task<int>(doStuff, {1});

    Thread::TaskSystem tskSys;

    for (unsigned int i = 0; i < 9; i++)
    {
        tskSys.AddTask(new Thread::Task<int>(doStuff, {i}));
    }

    Thread::ThreadPool threadPool;
    threadPool.Run(&tskSys);

    Engine::Instance().GetPostProcessManager().AddProcess(kP);

}

void Game::Update(float deltaTime)
{
    printf("Update");
}
