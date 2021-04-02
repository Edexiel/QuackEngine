#include "Renderer/RendererInterface.hpp"

#include "Scene/Core/World.hpp"

using namespace Renderer;

void RendererInterface::Set(std::shared_ptr<RenderSystem> renderSystem,
                                     std::shared_ptr<CameraSystem> cameraSystem,
                                     std::shared_ptr<LightSystem> lightSystem)
{
    renderSystem = renderSystem;
    cameraSystem = cameraSystem;
    lightSystem = lightSystem;
}

Framebuffer RendererInterface::GetSceneUpdatedFramebuffer()
{
    lightSystem->Update();
    Component::Camera& camera = cameraSystem->GetActiveCamera();
    renderSystem->Draw(camera);
    return camera.GetFramebuffer();
}


void RendererInterface::AddShaderToUpdate(const Shader &shader)
{
    lightSystem->AddShaderToUpdate(shader);
}

void RendererInterface::RemoveShaderFromUpdate(const Shader &shader)
{
    lightSystem->RemoveShaderFromUpdate(shader);
}

void RendererInterface::DrawFramebufferinFrambuffer(const Framebuffer& framebufferDrawIn, const Framebuffer& framebuffer2DrawOut)
{
    renderSystem->DrawTextureInFramebuffer(framebufferDrawIn.GetId(), framebuffer2DrawOut.GetTexture());
}

void RendererInterface::DrawTextureinFramebuffer(const Framebuffer& framebufferDrawIn, const Texture& textureDrawOut)
{
    renderSystem->DrawTextureInFramebuffer(framebufferDrawIn.GetId(), textureDrawOut.GetID());
}
