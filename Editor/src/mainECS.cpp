//
// Created by gnisi on 24/03/2021.
//
#include "Scene/Core/Ecs.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Core/ComponentManager.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"

using namespace Maths;

int main()
{
    Ecs ecs{};
    ecs.Init();

    ecs.RegisterComponent<Transform>();
    Signature signature;
    signature.set(ecs.GetComponentType<Transform>());
    ecs.SetSystemSignature<>();

    Entity& entity = ecs.CreateEntity("first");
    ecs.AddComponent(entity, Transform{Vector3f::Zero(), Vector3f::One(), Quaternion{}});
    ecs.

}