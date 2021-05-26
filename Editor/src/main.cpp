#include "GLFW/glfw3.h"

#include "Editor.hpp"
#include "Engine.hpp"

#include "Renderer/Shape.hpp"
#include "Renderer/RendererPlatform.hpp"

#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/System/CameraSystem.hpp"
#include "Scene/System/LightSystem.hpp"

#include "Tools/Random.hpp"
#include "game.hpp"
#include "Debug/Log.hpp"

using namespace Component;
using namespace Resources;


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

    Engine engine(settings);
    Engine::SetInstance(engine);

    Editor editor{engine.GetWindow()};

    Game game;
    game.Init(engine);

//    // Time && fps
//    double tempTime{0.0};
//    double time{0.0};
//    double deltaTime{0.0};
//    unsigned int frames{0};
//    double timeAcc{0.0};

    engine.GetPhysicsManager();
    engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();

    auto physicsSystem = engine.GetCurrentWorld().GetSystem<PhysicsSystem>();

    while (!engine.WindowShouldClose())
    {
//        // DeltaTime
//        {
//            tempTime = glfwGetTime();
//            deltaTime = tempTime - time;
//            time = tempTime;
//
//            timeAcc += deltaTime;
//            frames++;
//
//            if (timeAcc >= 1.0f)
//            {
//                std::cout << "FPS: " << round(1 / (timeAcc / frames)) << std::endl;
//                frames = 0;
//                timeAcc = 0.;
//            }
//        }
        const auto deltaTime = (float)engine.GetTimeManager().GetDeltaTime();

        /** POLL INPUT **/
        engine.GetInputManager().Update();
        engine.TestWindowShouldClose();


        /** Editor draw **/
        editor.Draw();

        if (engine.IsGamePlaying())
        {
            /** Time Update **/
            engine.GetTimeManager().Update();

            /** UPDATE **/
            engine.GetCurrentWorld().GetSystem<PhysicsSystem>()->FixedUpdate(deltaTime);
            engine.GetCurrentWorld().GetSystem<CameraSystem>()->Update();
        }
        engine.SwapBuffers();
        Renderer::RendererPlatform::Clear();
    }

    //engine.SaveWorld("Main","./");

    return 0;
}