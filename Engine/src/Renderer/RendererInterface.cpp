#include "Renderer/RendererInterface.hpp"

#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Scene/Component/Model.hpp"
#include "Scene/Component/Camera.hpp"

#include "Scene/Component/Model.hpp"

#include "Scene/System/CameraSystem.hpp"
#include "Scene/System/RenderSystem.hpp"
#include "Scene/System/LightSystem.hpp"

using namespace Renderer;

Framebuffer RendererInterface::GetSceneUpdatedFramebuffer()
{
    Component::Camera& camera = Engine::Instance().GetCurrentWorld().GetSystemManager()->GetSystem<CameraSystem>()->GetActiveCamera();
    Engine::Instance().GetCurrentWorld().GetSystemManager()->GetSystem<RenderSystem>()->Draw(camera);

    Engine::Instance().GetPostProcessManager().ApplyPostProcess(camera.GetFramebuffer());

    RendererPlatform::BindFramebuffer(0);

    return camera.GetFramebuffer();
}

void RendererInterface::UpdateSceneFramebufferEditor(const Maths::Matrix4& projection, const Maths::Matrix4& view, Framebuffer& framebuffer)
{
    framebuffer.Bind();

    Engine::Instance().GetCurrentWorld().GetSystemManager()->GetSystem<RenderSystem>()->Draw(projection, view);

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
