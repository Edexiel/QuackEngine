#include "Renderer/RendererManager.hpp"

#include "Scene/Core/World.hpp"
#include "Scene/Component/Model.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Component/Light.hpp"
#include "Scene/Component/Camera.hpp"
#include "Renderer/Shape.hpp"

#include "Renderer/RendererPlatform.hpp"

using namespace Renderer;

void RendererManager::Init(World *world)
{
    _world = world;

    world->RegisterComponent<Transform>(); //todo create a manager or a place to add Transform as a component


    world->RegisterComponent<Component::Model>();
    world->RegisterComponent<Component::Camera>();
    world->RegisterComponent<Component::Light>();

    _renderSystem = world->RegisterSystem<RenderSystem>();
    _cameraSystem = world->RegisterSystem<CameraSystem>();
    _lightSystem  = world->RegisterSystem<LightSystem>();

    Signature signatureRender;
    signatureRender.set(world->GetComponentType<Component::Model>());
    signatureRender.set(world->GetComponentType<Transform>());
    world->SetSystemSignature<RenderSystem>(signatureRender);

    Signature signatureCamera;
    signatureCamera.set(world->GetComponentType<Component::Camera>());
    signatureCamera.set(world->GetComponentType<Transform>());
    world->SetSystemSignature<CameraSystem>(signatureCamera);

    Signature signatureLight;
    signatureLight.set(world->GetComponentType<Component::Light>());
    signatureLight.set(world->GetComponentType<Transform>());
    world->SetSystemSignature<LightSystem>(signatureLight);

    _quadMesh = Renderer::Shape::CreateQuad();
    _shader = World::Instance().GetResourcesManager().LoadShader(
            "../../Engine/Shader/Framebuffer/BasicVertex.vs",
            "../../Engine/Shader/Framebuffer/BasicFragment.fs");
}

void RendererManager::Clear()
{
    _cameraSystem->Clear();
}


void RendererManager::InitWindow(unsigned int width, unsigned int height, const char* name)
{
    //_window.Init(width, height, name);
    //RendererPlatform::LoadGL();
}

Window RendererManager::GetWindow() const
{
    return _window;
}

void RendererManager::Update()
{
    _lightSystem->Update();

    Component::Camera& camera = _cameraSystem->GetActiveCamera();

    //RendererPlatform::EnableDepthBuffer(true);

    camera.GetFramebuffer().Bind();
    RendererPlatform::ClearColor({0.0f, 0.5f, 0.5f, 1.f});
    RendererPlatform::Clear();

    _renderSystem->Draw(camera.GetProjection(), camera.GetView());

    RendererPlatform::BindFramebuffer(0);

    RendererPlatform::ClearColor({0.2f, 0.2f, 0.2f, 1.f});
    RendererPlatform::Clear();

    _shader.Use();
    _shader.SetMatrix4("view", Maths::Matrix4::Identity());
    camera.GetFramebuffer().BindTexture();

    _quadMesh.Draw();

}

Framebuffer RendererManager::GetCameraFrame(Component::Camera &camera)
{
    return camera.GetFramebuffer();
}

void RendererManager::AddShaderToUpdate(const Shader &shader)
{
    _lightSystem->AddShaderToUpdate(shader);
}

void RendererManager::RemoveShaderFromUpdate(const Shader &shader)
{
    _lightSystem->RemoveShaderFromUpdate(shader);
}
