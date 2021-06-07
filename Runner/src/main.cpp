#include "Engine.hpp"

#include <Renderer/RendererPlatform.hpp>
#include <Scene/System/CharacterControllerSystem.hpp>
#include <Scene/System/AnimatorSystem.hpp>
#include <Scene/System/LightSystem.hpp>
#include <Player/PlayerSystem.hpp>
#include "Renderer/Framebuffer.hpp"
#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/System/CameraGameplaySystem.hpp"
#include "Scene/System/CameraSystem.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Renderer/PostProcessManager.hpp"
#include "Enemy/EnemySpawnSystem.hpp"
#include "Enemy/EnemySystem.hpp"


#include "Scene/Core/World.hpp"

#include "game.hpp"

int main()
{
    EngineSettings settings{
            true,
            "The Legend of Quack : the Kazoo of power",
            {1920, 1080},
            WINDOW_MODE::FULLSCREEN,
            0,
            INPUT_MODE::GLFW
    };

    Engine engine(settings);
    Engine::SetInstance(engine);

    Game::Init(engine);

    engine.GetCurrentWorld().GetSystem<CameraSystem>()->GetActiveCamera().Resize(1920, 1080);

    while (!engine.WindowShouldClose())
    {

        /** Time Update **/
        engine.UpdateTime();
        const auto deltaTime = (float) engine.GetDeltaTime();

        /** POLL INPUT **/
        engine.GetInputManager().Update();
        engine.TestWindowShouldClose();


        engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();


        /** UPDATE **/
        engine.GetCurrentWorld().GetSystem<PhysicsSystem>()->FixedUpdate(deltaTime);
        engine.GetCurrentWorld().GetSystem<CharacterControllerSystem>()->Update();
        engine.GetCurrentWorld().GetSystem<CameraGameplaySystem>()->Update();
        engine.GetCurrentWorld().GetSystem<Renderer::AnimatorSystem>()->Update();
        engine.GetCurrentWorld().GetSystem<PlayerSystem>()->Update();

        engine.GetCurrentWorld().GetSystem<EnemySpawnSystem>()->Update();
        engine.GetCurrentWorld().GetSystem<EnemySystem>()->Update();

        Renderer::Framebuffer f = Renderer::RendererInterface::GetSceneUpdatedFramebuffer();
        engine.GetPostProcessManager().DrawTextureInFramebuffer(0,f.GetTexture());

        engine.SwapBuffers();
        Renderer::RendererPlatform::Clear();
    }

    return 0;
}
