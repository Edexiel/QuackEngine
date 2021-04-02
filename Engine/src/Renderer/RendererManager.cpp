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


    //todo generate the component elsewhere

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


    _renderSystem->Init();

}

void RendererManager::Clear()
{
    _cameraSystem->Clear();
}

void RendererManager::Update()
{
    _lightSystem->Update();
//    _cameraSystem->Update();
    Component::Camera& camera = _cameraSystem->GetActiveCamera();
    _renderSystem->Update(camera);
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
