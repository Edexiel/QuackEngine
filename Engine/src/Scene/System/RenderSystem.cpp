#include "Scene/System/RenderSystem.hpp"

#include "Scene/Component/Transform.hpp"
#include "Scene/Component/Model.hpp"

#include "Scene/Core/World.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Scene/Component/Camera.hpp"
#include "Renderer/Shape.hpp"

using namespace Renderer;

RenderSystem::RenderSystem()
{
    _quadMesh = Shape::CreateQuad();
    _shader = World::Instance().GetResourcesManager().LoadShader(
            "../../Engine/Shader/Framebuffer/BasicVertex.vs",
            "../../Engine/Shader/Framebuffer/BasicFragment.fs");
}

void RenderSystem::Draw( Component::Camera& camera)
{
    camera.GetFramebuffer().Bind();

    RendererPlatform::ClearColor({0.0f, 0.0f, 0.0f, 1.f});
    RendererPlatform::Clear();

    for (Entity entity: _entities)
    {
        auto &t = World::Instance().GetComponent<Transform>(entity);
        auto &m = World::Instance().GetComponent<Component::Model>(entity);

        m.Draw(camera.GetProjection(), camera.GetView(), t.GetMatrix());
    }
}

void RenderSystem::DrawTextureInFramebuffer(unsigned int framebufferIndex, unsigned int textureIndex)
{
    RendererPlatform::BindFramebuffer(framebufferIndex);

    RendererPlatform::ClearColor({0.2f, 0.2f, 0.2f, 1.f});
    RendererPlatform::Clear();

    _shader.Use();
    _shader.SetMatrix4("view", Maths::Matrix4::Identity());
    RendererPlatform::BindTexture(textureIndex, 0);

    _quadMesh.Draw();
}