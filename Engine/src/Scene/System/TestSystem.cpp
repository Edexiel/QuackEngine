//
// Created by gnisi on 25/03/2021.
//
#include "Scene/Core/World.hpp"

#include "Scene/System/TestSystem.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Core/Types.hpp"
#include <cstdio>

TestSystem::TestSystem()
{
    std::printf("Construct TestSystem\n");
}

void TestSystem::Init()
{
    std::printf("Init");

}

void TestSystem::FixedUpdate(float fixedUpdate)
{
    std::printf("FixedUpdate");

}

void TestSystem::Update(float deltaTime)
{

    for (Entity entity: _entities) {
        auto& t = World::Instance().GetComponent<Transform>(entity);

        std::printf("x: %f y: %f z:%f\n",t.position.x,t.position.y,t.position.z);

    }


}