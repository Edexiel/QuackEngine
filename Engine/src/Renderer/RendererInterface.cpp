#include "Renderer/RendererInterface.hpp"

#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Renderer/RendererPlatform.hpp"

using namespace Renderer;

void RendererInterface::Set(std::shared_ptr<RenderSystem> _renderSystem,
                                     std::shared_ptr<CameraSystem> _cameraSystem,
                                     std::shared_ptr<LightSystem> _lightSystem)
{
    //todo: nettoyer
    renderSystem = _renderSystem;
    cameraSystem = _cameraSystem;
    lightSystem = _lightSystem;
}

Framebuffer RendererInterface::GetSceneUpdatedFramebuffer()
{
    lightSystem->Update();
    Component::Camera& camera = cameraSystem->GetActiveCamera();
    renderSystem->Draw(camera);

    RendererPlatform::BindFramebuffer(0);

    return camera.GetFramebuffer();
}

void RendererInterface::UpdateSceneFramebufferEditor(const Maths::Matrix4& projection, const Maths::Matrix4& view, Framebuffer& framebuffer)
{
    framebuffer.Bind();

    lightSystem->Update();
    renderSystem->Draw(projection, view);
    Engine::Instance().GetPostProcessManager().ApplyPostProcess(framebuffer);

    RendererPlatform::BindFramebuffer(0);
}

void RendererInterface::DrawFramebufferinFramebuffer(const Framebuffer& framebufferDrawIn, const Framebuffer& framebufferDrawOut)
{
    Engine::Instance().GetPostProcessManager().DrawTextureInFramebuffer(framebufferDrawIn.GetId(), framebufferDrawOut.GetTexture());
}

void RendererInterface::DrawTextureinFramebuffer(const Framebuffer& framebufferDrawIn, const Texture& textureDrawOut)
{
    Engine::Instance().GetPostProcessManager().DrawTextureInFramebuffer(framebufferDrawIn.GetId(), textureDrawOut.GetID());
}
