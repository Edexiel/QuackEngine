//
// Created by gnisi on 24/03/2021.
//
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Core/ComponentManager.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"
#include "Scene/System/TestSystem.hpp"

using namespace Maths;

int main()
{
    World ecs{};
    ecs.Init();

    ecs.RegisterComponent<Transform>();
    auto testSystem = ecs.RegisterSystem<TestSystem>();

    Signature signature;
    signature.set(ecs.GetComponentType<Transform>());
    ecs.SetSystemSignature<TestSystem>(signature);

    Entity id = ecs.CreateEntity("Test");
    Entity idd = ecs.CreateEntity("Test2");
    ecs.AddComponent(id, Transform{Vector3f::Zero(), Vector3f::One(), Quaternion{}});

    float dt = 0.0f;

    while (true)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        testSystem->Update(dt);
        auto stopTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    }
}