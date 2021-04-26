#include "GLFW/glfw3.h"

#include "Editor.hpp"
#include "Engine.hpp"
#include "Renderer/Material.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Scene/Component/RigidBody.hpp"
#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/System/CameraSystem.hpp"
#include "Resources/ResourcesManager.hpp"

#include "Tools/Random.hpp"
#include "CameraEditor.hpp"

#include "reactphysics3d/reactphysics3d.h"

using namespace Renderer;
using namespace Component;
using namespace Resources;

// todo: remove this vars and class when you can have access of the PhysicsSystem
std::shared_ptr<PhysicsSystem> tempPhysicsSystemPtr;

class EventLisenerTemp : public rp3d::EventListener
{
    virtual void onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData)
    {
        std::cout << "OnTrigger\n";
    }
    virtual void onContact(const rp3d::CollisionCallback::CallbackData& callbackData)
    {
        std::cout << "OnContact\n";
        for (unsigned int p = 0; p < callbackData.getNbContactPairs(); p++)
        {

            // Get the contact pair
            CollisionCallback::ContactPair contactPair = callbackData.getContactPair(p);

            // For each contact point of the contact pair
            for (unsigned int c = 0; c < contactPair.getNbContactPoints(); c++)
            {

                // Get the contact point
                CollisionCallback::ContactPoint contactPoint = contactPair.getContactPoint(c);

                // Get the contact point on the first collider and convert it in world-space
                rp3d::Vector3 worldPoint = contactPair.getCollider1()->getLocalToWorldTransform() *
                                           contactPoint.getLocalPointOnCollider1();
//                std::cout <<"Collision point: "<< worldPoint.x << ", " <<  worldPoint.y << ", " <<  worldPoint.z << std::endl;
            }
        }
    }
};

EventLisenerTemp eventLisener;

void loadScene()
{

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
    }

    auto renderSystem = world.RegisterSystem<RenderSystem>();
    auto cameraSystem = world.RegisterSystem<CameraSystem>();
    auto lightSystem = world.RegisterSystem<LightSystem>();
    auto physicsSystem = world.RegisterSystem<PhysicsSystem>();

    Engine &engine = Engine::Instance();

    engine.GetRendererInterface().Set(renderSystem, cameraSystem, lightSystem);
    engine.GetResourcesManager().Init();
    engine.GetResourcesManager().LoadFolder(R"(..\..\Game\Asset)");


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

    //Signature Physics
    {
        Signature signaturePhysics;
        signaturePhysics.set(world.GetComponentType<Transform>());
        signaturePhysics.set(world.GetComponentType<Component::RigidBody>());
        world.SetSystemSignature<PhysicsSystem>(signaturePhysics);
    }

    physicsSystem->Init();
    tempPhysicsSystemPtr = physicsSystem;
    world.GetPhysicsWorld()->setEventListener(&eventLisener);
//    CameraEditor cam;
//    cam.SetInput(engine.GetInputManager());

    {
        Entity CameraEntity = world.CreateEntity("Camera");

        Component::Camera camera(1280,
                                 720,
                                 1000, -1, 20 * 3.1415 / 180);

        Transform cameraTrs;
        cameraTrs.position = {0, 0, -5};
        world.AddComponent(CameraEntity, camera);
        world.AddComponent(CameraEntity, cameraTrs);
    }
    ResourcesManager &resourcesManager = Engine::Instance().GetResourcesManager();

    Transform t = {Maths::Vector3f{0, 0, 10}, Maths::Vector3f::One() * 1.5f, Maths::Quaternion{}};
    Component::Model md = engine.GetResourcesManager().LoadModel(R"(..\..\Game\Asset\Model\Sphere.fbx)", Renderer::VertexType::V_NORMALMAP);

    Material material;

    material.ambient = {1, 1, 1};
    material.diffuse = {1, 1, 1};
    material.specular = {1, 1, 1};
    material.checkLight = true;
    material.normalMap = engine.GetResourcesManager().LoadTexture(R"(..\..\Game\Asset\Texture\Floor_N.jpg)");

    MaterialInterface materialInterface = resourcesManager.GenerateMaterial("base", material);

    md.AddMaterial(materialInterface);


    for (int x = 0; x < 1; x++)
    {
        for (int  y = 0; y < 1; y++)
        {
            for (int  z = 0; z < 1; z++)
            {
                t.position.x = 0;
                t.position.y = 10.f /*- (float)y * 2*/;
                t.position.z = 20.f /*+ (float)z * 2*/;

                Entity id = world.CreateEntity("Sphere");

                Component::RigidBody rb;

                world.AddComponent(id, t);
                world.AddComponent(id, md);
                world.AddComponent(id, rb);

                physicsSystem->SetRigidBody(id);
                physicsSystem->SetType(id, BodyType::DYNAMIC);

                physicsSystem->AddSphereCollider(id, 1.5f);
            }
        }
    }

    //Test triggerCollision
    Component::RigidBody rbTrigger;
    Component::Model mdTrigger = engine.GetResourcesManager().LoadModel(R"(..\..\Game\Asset\Model\Cube.fbx)", Renderer::VertexType::V_NORMALMAP);
    Transform tTrigger = {Maths::Vector3f{0, -2.5f, 20}, {1,1,1}, Maths::Quaternion{}};
    Entity idTrigger = world.CreateEntity("TriggerBox");

    world.AddComponent(idTrigger, tTrigger);
    world.AddComponent(idTrigger, mdTrigger);
    world.AddComponent(idTrigger, rbTrigger);

    physicsSystem->SetRigidBody(idTrigger);
    physicsSystem->SetType(idTrigger, BodyType::STATIC);
    physicsSystem->AddBoxCollider(idTrigger,{1,1,1});
    physicsSystem->SetIsTrigger(idTrigger, true);

//Test triggerCollision
    Component::RigidBody rbContact;
    Component::Model mdContact = engine.GetResourcesManager().LoadModel(R"(..\..\Game\Asset\Model\Cube.fbx)", Renderer::VertexType::V_NORMALMAP);
    Transform tContact = {Maths::Vector3f{0, -5.f, 20}, {1,1,1}, Maths::Quaternion{}};
    Entity idContact = world.CreateEntity("ContactBox");

    world.AddComponent(idContact, tContact);
    world.AddComponent(idContact, mdContact);
    world.AddComponent(idContact, rbContact);

    physicsSystem->SetRigidBody(idContact);
    physicsSystem->SetType(idContact, BodyType::STATIC);
    physicsSystem->AddBoxCollider(idContact,{1,1,1});

    Entity idFloor = world.CreateEntity("Floor");

    Maths::Vector3f scale{20, 0.25, 20};
    Transform tFloor = {Maths::Vector3f{0, -5, 20}, scale, Maths::Quaternion{}};


    Component::RigidBody rbFloor;
    Component::Model mdFloor = engine.GetResourcesManager().LoadModel(R"(..\..\Game\Asset\Model\Cube.fbx)", Renderer::VertexType::V_NORMALMAP);

    material.colorTexture = engine.GetResourcesManager().LoadTexture(R"(..\..\Game\Asset\Texture\Floor_C.jpg)");

    MaterialInterface materialInterface2 = resourcesManager.GenerateMaterial("mat2", material);

    mdFloor.AddMaterial(materialInterface2);

    world.AddComponent(idFloor, tFloor);
    world.AddComponent(idFloor, mdFloor);
    world.AddComponent(idFloor, rbFloor);

    physicsSystem->SetRigidBody(idFloor);
    physicsSystem->SetType(idFloor, BodyType::STATIC);
    physicsSystem->AddBoxCollider(idFloor, scale);


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
}

int main()
{
    EngineSettings settings{
            true,
            "QuackEditor",
            {1280, 720},
            WINDOW_MODE::WINDOWED,
            0,
            INPUT_MODE::GLFW
    };

    Engine &engine = Engine::Instance();
    engine.InitWindow(settings);

    Editor editor{engine.GetWindow()};

    loadScene();

    // Time && fps
    double tempTime{0.0};
    double time{0.0};
    double deltaTime{0.0};
    unsigned int frames{0};
    double timeAcc{0.0};

    engine.GetRendererInterface().lightSystem->Update();
    engine.GetPhysicsManager();
    while (!engine.WindowShouldClose())
    {
        // DeltaTime
        {
            tempTime = glfwGetTime();
            deltaTime = tempTime - time;
            time = tempTime;

            timeAcc += deltaTime;
            frames++;

            if (timeAcc >= 1.0f)
            {
                std::cout << "FPS: " << round(1 / (timeAcc / frames)) << std::endl;
                frames = 0;
                timeAcc = 0.;
            }
        }

        /** POLL INPUT **/
        engine.GetInputManager().Update();
        engine.TestWindowShouldClose();


        Renderer::RendererPlatform::ClearColor({0.7f, 0.7f, 0.7f, 0.f});
        Renderer::RendererPlatform::Clear();

        /** Editor draw **/
        editor.Draw();

        /** UPDATE **/
        tempPhysicsSystemPtr->FixedUpdate(deltaTime);

        engine.SwapBuffers();
    }

    return 0;
}