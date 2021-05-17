#include "Renderer/RendererInterface.hpp"

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

void RendererInterface::UpdateSceneFramebufferEditor(const Maths::Matrix4& projection, const Maths::Matrix4& view, unsigned int idFramebuffer)
{
    RendererPlatform::BindFramebuffer(idFramebuffer);

    lightSystem->Update();
    renderSystem->Draw(projection, view);

    RendererPlatform::BindFramebuffer(0);
}

void RendererInterface::DrawFramebufferinFramebuffer(const Framebuffer& framebufferDrawIn, const Framebuffer& framebuffer2DrawOut)
{
    renderSystem->DrawTextureInFramebuffer(framebufferDrawIn.GetId(), framebuffer2DrawOut.GetTexture());
}

void RendererInterface::DrawTextureinFramebuffer(const Framebuffer& framebufferDrawIn, const Texture& textureDrawOut)
{
    renderSystem->DrawTextureInFramebuffer(framebufferDrawIn.GetId(), textureDrawOut.GetID());
}
