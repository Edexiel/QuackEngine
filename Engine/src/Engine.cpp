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
    ecs.Init(input);

    World::Instance().GetInputManager();


    //ecs.RegisterComponent<Transform>();
    //ecs.RegisterComponent<Component::Model>();
    auto testSystem = ecs.RegisterSystem<TestSystem>();
    auto renderSystem = ecs.RegisterSystem<RenderSystem>();

    Signature signature;
    signature.set(ecs.GetComponentType<Transform>());
    ecs.SetSystemSignature<TestSystem>(signature);

    Signature signatureRender;
    signatureRender.set(ecs.GetComponentType<Component::Model>());
    signatureRender.set(ecs.GetComponentType<Transform>());
    ecs.SetSystemSignature<RenderSystem>(signatureRender);


    Entity id = ecs.CreateEntity("Test");
    Transform t = {Vector3f::One(), Vector3f::One(), Quaternion{}};
    ecs.AddComponent(id, t);

    Entity idRenderTest = ecs.CreateEntity("Test");
    Transform t2 = {Vector3f{0, 1, 0}, Vector3f::One(), Quaternion{}};
    Component::Model md;
    ecs.AddComponent(idRenderTest, t2);
    ecs.AddComponent(idRenderTest, md);
}


void Engine::Update()
{



}
