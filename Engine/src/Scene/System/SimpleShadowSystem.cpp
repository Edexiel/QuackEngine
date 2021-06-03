#include "Scene/System/SimpleShadowSystem.hpp"

#include "Renderer/Mesh.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/RendererPlatform.hpp"

#include "Scene/Component/Transform.hpp"

#include "Engine.hpp"
#include "Scene/Core/World.hpp"

#include "Scene/System/CameraSystem.hpp"

using namespace Renderer;

SimpleShadowSystem::SimpleShadowSystem()
{
    _listShadowShader.resize(2);
    _listShadowShader[0] = Shader::LoadShader("./Shader/PostProcess/SquareShadow.qsh");
    _listShadowShader[1] = Shader::LoadShader("./Shader/PostProcess/CircleShadow.qsh");
}

void SimpleShadowSystem::Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh)
{
    Engine& engine = Engine::Instance();
    World& world = engine.GetCurrentWorld();

    auto& camera = world.GetSystem<CameraSystem>()->GetActiveCamera();

    buffer.Bind();
    RendererPlatform::EnableDepthBuffer(true);
    RendererPlatform::SetTransparency(true);

    for (unsigned int i = 0 ; i < _listShadowShader.size(); i++)
    {
        Shader& shader = _listShadowShader[i];
        shader.Use();
        shader.SetMatrix4("projection", camera.GetProjection());
        shader.SetMatrix4("view", camera.GetView());
        shader.SetVector4f("color", {0,0,0,0.7f});
    }

    for (Entity entity: _entities)
    {
        auto &transform = world.GetComponent<Component::Transform>(entity);
        auto &shadow = world.GetComponent<Component::SimpleShadow>(entity);

        Shader& shader = _listShadowShader[shadow.type];

        shader.Use();
        shader.SetMatrix4("model", Maths::Matrix4::Translate(transform.position + shadow.offset)
                * Maths::Quaternion::EulerToQuaternion({Pi<float>()/2.f, 0, 0}).ToMatrix()
                * Maths::Matrix4::Scale(transform.scale * shadow.scale));

        screenMesh.Draw();
    }
}

void SimpleShadowProcess::Process(const Framebuffer &buffer, const Mesh &screenMesh)
{
    Engine::Instance().GetCurrentWorld().GetSystem<SimpleShadowSystem>()->Process(buffer, screenMesh);
}
