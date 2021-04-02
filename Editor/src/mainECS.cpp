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