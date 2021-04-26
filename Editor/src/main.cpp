#include <Renderer/RendererPlatform.hpp>
#include "GLFW/glfw3.h"

#include "Editor.hpp"
#include "Engine.hpp"
#include "Tools/Random.hpp"
#include "CameraEditor.hpp"
#include "Scene/System/PhysicsSystem.hpp"
#include "game.hpp"

#include "Scene/Component/RigidBody.hpp"
//#include "reactphysics3d/reactphysics3d.h"

using namespace Renderer;
using namespace Component;
using namespace Resources;

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
//    CameraEditor cam;
//    cam.SetInput(engine.GetInputManager());

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

    Game game;
    game.Init();

    // Time && fps
    double tempTime{0.0};
    double time{0.0};
    double deltaTime{0.0};
    unsigned int frames{0};
    double timeAcc{0.0};

    engine.GetRendererInterface().lightSystem->Update();
    engine.GetPhysicsManager();

    auto physicsSystem = engine.GetCurrentWorld().GetSystemManager()->GetSystem<PhysicsSystem>();

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


        /** Editor draw **/
        editor.Draw();

        /** UPDATE **/
        engine.GetCurrentWorld().GetSystemManager()->GetSystem<PhysicsSystem>()->FixedUpdate(deltaTime);

        engine.SwapBuffers();
    }

    return 0;
}