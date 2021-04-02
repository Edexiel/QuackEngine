//
// Created by g.nisi on 3/9/21.
//

#include <Scene/Component/Transform.hpp>
#include <Scene/System/TestSystem.hpp>
#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Maths/Vector3.hpp"

using namespace Maths;

void Engine::Init(Input::PlatformInput &input)
{

    World &ecs = World::Instance();

    World::Instance().GetInputManager();


    ecs.RegisterComponent<Transform>();

    ecs.RegisterComponent<Component::Model>();
    ecs.RegisterComponent<Component::Camera>();
    ecs.RegisterComponent<Component::Light>();

    auto renderSystem = ecs.RegisterSystem<RenderSystem>();
    auto cameraSystem = ecs.RegisterSystem<CameraSystem>();
    auto lightSystem  = ecs.RegisterSystem<LightSystem>();

    Signature signatureRender;
    signatureRender.set(ecs.GetComponentType<Component::Model>());
    signatureRender.set(ecs.GetComponentType<Transform>());
    ecs.SetSystemSignature<RenderSystem>(signatureRender);

    Signature signatureCamera;
    signatureCamera.set(ecs.GetComponentType<Component::Camera>());
    signatureCamera.set(ecs.GetComponentType<Transform>());
    ecs.SetSystemSignature<CameraSystem>(signatureCamera);

    Signature signatureLight;
    signatureLight.set(ecs.GetComponentType<Component::Light>());
    signatureLight.set(ecs.GetComponentType<Transform>());
    ecs.SetSystemSignature<LightSystem>(signatureLight);

    ecs.GetRendererInterface().Set(renderSystem, cameraSystem, lightSystem);

    ecs.Init(input);
}


void Engine::Update()
{



}
