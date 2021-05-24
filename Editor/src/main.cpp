#include "GLFW/glfw3.h"

#include "Editor.hpp"
#include "Engine.hpp"
#include "Renderer/Shape.hpp"
#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/System/CameraSystem.hpp"

#include "Tools/Random.hpp"
#include "game.hpp"

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
        //engine.GetCurrentWorld().GetSystemManager()->GetSystem<PhysicsSystem>()->FixedUpdate(deltaTime);
        engine.GetCurrentWorld().GetSystemManager()->GetSystem<CameraSystem>()->Update();

        engine.SwapBuffers();
    }

    //engine.SaveWorld("Main","./");

    return 0;
}