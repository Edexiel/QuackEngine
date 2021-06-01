#include "GLFW/glfw3.h"

#include "Editor.hpp"
#include "Engine.hpp"

#include "Renderer/RendererPlatform.hpp"

#include "Scene/System/CameraSystem.hpp"
#include "Scene/System/LightSystem.hpp"
#include "Scene/System/AnimatorSystem.hpp"
#include "Scene/System/CharacterControllerSystem.hpp"
#include "Scene/System/PhysicsSystem.hpp"

#include "Scene/System/AnimatorSystem.hpp"
#include "Scene/System/CameraGameplaySystem.hpp"

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

    engine.GetPhysicsManager();
    engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();

    while (!engine.WindowShouldClose())
    {

        /** Time Update **/
        engine.UpdateTime();

        const auto deltaTime = (float) engine.GetDeltaTime();

        /** POLL INPUT **/
        engine.GetInputManager().Update();
        engine.TestWindowShouldClose();

        /** Editor draw **/
        editor.Draw();

        if (engine.IsGamePlaying())
        {
            /** UPDATE **/
            engine.GetCurrentWorld().GetSystem<PhysicsSystem>()->FixedUpdate(deltaTime);
            engine.GetCurrentWorld().GetSystem<CharacterControllerSystem>()->Update();
            engine.GetCurrentWorld().GetSystem<CameraGameplaySystem>()->Update();
            engine.GetCurrentWorld().GetSystem<Renderer::AnimatorSystem>()->Update();

        }
        engine.SwapBuffers();
        Renderer::RendererPlatform::Clear();
    }

    return 0;
}