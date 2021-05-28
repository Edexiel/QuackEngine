#include <Renderer/RendererPlatform.hpp>
#include "Engine.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Scene/System/RenderSystem.hpp"
#include "game.hpp"

int main()
{
    EngineSettings settings{
            false,
            "Game",
            {1280, 720},
            WINDOW_MODE::WINDOWED,
            0,
            INPUT_MODE::GLFW
    };

    Engine engine(settings);
    Engine::SetInstance(engine);

    Game game;
    game.Init();
    //loadScene();

    while (!engine.WindowShouldClose())
    {
        /** POLL INPUT **/
        engine.GetInputManager().Update();
        engine.TestWindowShouldClose();


//        Renderer::RendererPlatform::ClearColor({0.7f, 0.7f, 0.7f, 0.f});
//        Renderer::RendererPlatform::Clear();

        //display FB
        Renderer::RendererInterface &rendererInterface = Engine::Instance().GetRendererInterface();

        //rendererInterface.cameraSystem->GetActiveCamera().Resize(wsize.x, wsize.y);
        //Renderer::Framebuffer f = rendererInterface.GetSceneUpdatedFramebuffer();
        //rendererInterface.renderSystem->DrawTextureInFramebuffer(0, f.GetTexture());


        /** UPDATE **/
//        physicsSystem->FixedUpdate(deltaTime);

        engine.SwapBuffers();
    }

    return 0;
}
