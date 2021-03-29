//
// Created by gnisi on 25/03/2021.
//

#include "Scene/System/TestSystem.hpp"
#include "Scene/Core/Ecs.hpp"
#include <cstdio>

TestSystem::TestSystem()
{
    std::printf("Construct TestSystem");
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
    std::printf("Update");

}