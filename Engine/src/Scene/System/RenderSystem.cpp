#include "Scene/System/RenderSystem.hpp"

#include "Scene/Component/Transform.hpp"
#include "Scene/Component/Model.hpp"

#include "Scene/Core/World.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Scene/Component/Camera.hpp"
#include "Renderer/Shape.hpp"

using namespace Renderer;

void RenderSystem::Init()
{
    _quadMesh = Shape::CreateQuad();
    _shader = World::Instance().GetResourcesManager().LoadShader(
            "../../Engine/Shader/Framebuffer/BasicVertex.vs",
            "../../Engine/Shader/Framebuffer/BasicFragment.fs");
}


void RenderSystem::Update(Component::Camera& camera)
{
    Draw(camera);

    RendererPlatform::BindFramebuffer(0);

    RendererPlatform::ClearColor({0.2f, 0.2f, 0.2f, 1.f});
    RendererPlatform::Clear();

    _shader.Use();
    _shader.SetMatrix4("view", Maths::Matrix4::Identity());
    camera.GetFramebuffer().BindTexture();

    _quadMesh.Draw();
}

void RenderSystem::Draw(Component::Camera& camera)
{
    RendererPlatform::ClearColor({0.0f, 0.0f, 0.0f, 1.f});
    RendererPlatform::Clear();

    camera.GetFramebuffer().Bind();

    //RendererPlatform::BindFramebuffer(0);


    for (Entity entity: _entities)
    {
        auto &t = World::Instance().GetComponent<Transform>(entity);
        auto &m = World::Instance().GetComponent<Component::Model>(entity);

        m.Draw(camera.GetProjection(), camera.GetView(), t.GetMatrix());
    }
}