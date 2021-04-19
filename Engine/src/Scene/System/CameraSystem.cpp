#include "Scene/System/CameraSystem.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"

Component::Camera& CameraSystem::GetActiveCamera()
{
    World& world = World::Instance();
    for (Entity entity: _entities) {
        auto &t = world.GetComponent<Component::Camera>(entity);
        if (t.isActive)
        {
            Transform trs = world.GetComponent<Transform>(entity);
            trs.position = trs.position * -1;
            t.SetView(trs.GetMatrix());
            return t;
        }
    }
    Assert_Fatal_Error(true, "No Camera Active");
    exit(-1);
}

void CameraSystem::Clear()
{
    for (Entity entity: _entities)
    {
        auto &t = World::Instance().GetComponent<Component::Camera>(entity);
        t.GetFramebuffer().Delete();
    }
}