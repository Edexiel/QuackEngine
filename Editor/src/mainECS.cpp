//
// Created by gnisi on 24/03/2021.
//
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Core/ComponentManager.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"
#include "Scene/System/TestSystem.hpp"
#include "Scene/System/RenderSystem.hpp"
#include "Scene/Component/Model.hpp"

using namespace Maths;

int main()
{
    World &ecs=World::Instance();
    ecs.Init();

    ecs.RegisterComponent<Transform>();
    ecs.RegisterComponent<Component::Model>();
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
    Transform t2 = {Vector3f{0,1,0}, Vector3f::One(), Quaternion{}};
    Component::Model md;
    ecs.AddComponent(idRenderTest, t2);
    ecs.AddComponent(idRenderTest, md);

    float dt = 0.0f;

    while (true)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        //testSystem->Update(dt);
        renderSystem->Draw(0);
        auto stopTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    }
}