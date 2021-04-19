#include "GLFW/glfw3.h"

#include "Input/InputManager.hpp"
#include "Input/PlatformInputGLFW.hpp"
#include "Editor.hpp"
#include "Engine.hpp"
#include "Renderer/Material.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shape.hpp"
#include "Scene/Component/RigidBody.hpp"
#include "Scene/System/PhysicsSystem.hpp"

#include "Tools/Random.hpp"

using namespace Renderer;
int main()
{
    Engine engine;
    Editor editor{engine};
    World &world = World::Instance();

    EngineSettings settings{
            true,
            "QuackEditor",
            {1280, 720},
            WINDOW_MODE::WINDOWED,
            0
    };
    editor.Init(settings);
    GLFWwindow *window = editor.GetWindow();
    Input::PlatformInputGLFW input{window};
    engine.Init(input);

    world.RegisterComponent<Component::RigidBody>();
    auto physicsSystem = world.RegisterSystem<PhysicsSystem>();

    Signature signature;
    signature.set(world.GetComponentType<Transform>());
    signature.set(world.GetComponentType<Component::RigidBody>());
    world.SetSystemSignature<PhysicsSystem>(signature);

    physicsSystem->Init();

    {
        Entity CameraEntity = world.CreateEntity("Camera");

        Component::Camera camera(1280,
                                 720,
                                 1000, -1, 20 * 3.1415 / 180);

        Transform cameraTrs;
        world.AddComponent(CameraEntity, camera);
        world.AddComponent(CameraEntity, cameraTrs);

    }

    Transform t = {Maths::Vector3f{0, 0, 10}, Maths::Vector3f::One() * 1.5f, Maths::Quaternion{}};
    Component::Model md = world.GetResourcesManager().LoadModel("../../Asset/Sphere.fbx", Renderer::VertexType::V_NORMALMAP);

    Material material;

    material.ambient = {1, 1, 1};
    material.diffuse = {1, 1, 1};
    material.specular = {1, 1, 1};
    material.checkLight = true;
    material.normalMap = world.GetResourcesManager().LoadTexture("../../Asset/Floor_N.jpg");

    MaterialInterface materialInterface = world.GetResourcesManager().GenerateMaterial("base", material);

    md.AddMaterial(materialInterface);


    for (int x = 0; x < 10; x++)
    {
        for (int  y = 0; y < 10; y++)
        {
            for (int  z = 0; z < 10; z++)
            {
                t.position.x = -10 + Random::Range(0, 20);
                t.position.y = 5 - y * 2;
                t.position.z = 20 + z * 2;

                Entity id = world.CreateEntity("Test");

                Component::RigidBody rb;

                world.AddComponent(id, t);
                world.AddComponent(id, md);
                world.AddComponent(id, rb);

                physicsSystem->SetRigidBody(id);
//                physicsSystem->SetType(id, BodyType::STATIC);

                physicsSystem->AddSphereCollider(id, 1.5f);
            }
        }
    }

    Entity idFloor = world.CreateEntity("Floor");

    Maths::Vector3f scale{20,0.25,20};
    Transform tFloor = {Maths::Vector3f{0, -5, 20}, scale, Maths::Quaternion{}};


    Component::RigidBody rbFloor;
    Component::Model mdFloor = world.GetResourcesManager().LoadModel("../../Asset/Cube.fbx", Renderer::VertexType::V_NORMALMAP);

    material.colorTexture = world.GetResourcesManager().LoadTexture("../../Asset/Floor_C.jpg");

    MaterialInterface materialInterface2 = world.GetResourcesManager().GenerateMaterial("mat2", material);

    mdFloor.AddMaterial(materialInterface2);

    world.AddComponent(idFloor, tFloor);
    world.AddComponent(idFloor, mdFloor);
    world.AddComponent(idFloor, rbFloor);

    physicsSystem->SetRigidBody(idFloor);
    physicsSystem->SetType(idFloor, BodyType::STATIC);
    physicsSystem->AddBoxCollider(idFloor, scale);


    Entity lightID = world.CreateEntity("Light");
    Entity lightID2 = world.CreateEntity("Light");
    Entity lightID3 = world.CreateEntity("Light");

    Component::Light light;

    light.type = Component::Light_Type::L_SPOT;
    light.ambient = {0.1f, 0.1f, 0.1f};
    light.diffuse = {1,0,0};
    light.specular = {1, 0, 0};
    light.constant = 1.0f;
    light.linear = 0.0014f;
    light.quadratic = 0.000007f;

    light.outerSpotAngle = 10.5;
    light.spotAngle = 8.5;


    Transform tl1 = {Maths::Vector3f::One(), Maths::Vector3f::One(), Maths::Quaternion{}};

    world.AddComponent(lightID, light);
    world.AddComponent(lightID, tl1);

    light.type = Component::Light_Type::L_POINT;
    light.diffuse = {1,1,1};
    light.specular = {1, 1, 1};
    Transform tl2 = {Maths::Vector3f::One() * -100, Maths::Vector3f::One(), Maths::Quaternion{}};

    world.AddComponent(lightID2, light);
    world.AddComponent(lightID2, tl2);

    light.type = Component::Light_Type::L_DIRECTIONAL;
    light.diffuse = {0,0,1};
    light.specular = {0, 0, 1};
    Transform tl3 = {Maths::Vector3f::Zero(), Maths::Vector3f::One(), Maths::Quaternion{3.1415 / 2, 1, 0, 0}};

    //Audio::Sound sound = world.GetSoundManager().CreateSound("../../../inactive.ogg", Audio::SoundType::S_MUSIC);
    //sound.Play();
    //sound.SetVolume(0.05f);

    world.AddComponent(lightID3, light);
    world.AddComponent(lightID3, tl3);

    Renderer::RendererPlatform::EnableDepthBuffer(true);

    float dt = 0;

    // Time && fps
    double temp_time{0.0};
    double time{0.0};
    double deltaTime{0.0};
    unsigned int frames{0};
    double time_acc{0.0};

    world.GetRendererInterface().lightSystem->Update();
    //world.GetRendererInterface().renderSystem->SetMaterials();

    world.GetResourcesManager().LoadFolder("../../Game/Asset/");

    while (!glfwWindowShouldClose(window))
    {
        { // DeltaTime
            temp_time = glfwGetTime();
            deltaTime = temp_time - time;
            time = temp_time;

            time_acc += deltaTime;
            frames++;

            if (time_acc >= 1.0f)
            {
                std::cout << "FPS: " << round(1 / (time_acc / frames)) << std::endl;
                frames = 0;
                time_acc = 0.;
            }

            //physicsSystem->FixedUpdate(deltaTime);

        }

        Renderer::RendererPlatform::ClearColor({0.7f,0.7f,0.7f,0.f});
        Renderer::RendererPlatform::Clear();
        editor.Draw();


        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, 1);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}