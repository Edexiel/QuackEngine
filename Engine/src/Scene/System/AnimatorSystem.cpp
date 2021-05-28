#include "Scene/System/AnimatorSystem.hpp"

#include "Engine.hpp"
#include "Scene/Core/World.hpp"

#include "Scene/Component/Animator.hpp"

using namespace Renderer;
using namespace Component;

void AnimatorSystem::Update()
{
    World &world = Engine::Instance().GetCurrentWorld();
    float deltaTime = Engine::Instance().GetTimeManager().GetDeltaTime();
    for (Entity entity: _entities)
    {
        auto &animator = world.GetComponent<Animator>(entity);

        animator.Update(deltaTime);
    }
}
