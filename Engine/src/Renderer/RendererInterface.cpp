#include "Renderer/RendererInterface.hpp"

#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Camera.hpp"
#include "Renderer/Framebuffer.hpp"

#include "Renderer/RendererPlatform.hpp"
#include "Scene/System/RenderSystem.hpp"
#include "Scene/System/CameraSystem.hpp"

#include "Maths/Matrix4.hpp"

using namespace Renderer;

Framebuffer RendererInterface::GetSceneUpdatedFramebuffer()
{
    Component::Camera& camera = Engine::Instance().GetCurrentWorld().GetSystem<CameraSystem>()->GetActiveCamera();
    Engine::Instance().GetCurrentWorld().GetSystem<RenderSystem>()->Draw(camera);

    Engine::Instance().GetPostProcessManager().ApplyPostProcess(camera.GetFramebuffer());

    RendererPlatform::BindFramebuffer(0);

    return camera.GetFramebuffer();
}

void RendererInterface::UpdateSceneFramebufferEditor(const Maths::Matrix4& projection, const Maths::Matrix4& view, const Framebuffer& framebuffer)
{
    framebuffer.Bind();

    Engine::Instance().GetCurrentWorld().GetSystem<RenderSystem>()->Draw(projection, view);

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
