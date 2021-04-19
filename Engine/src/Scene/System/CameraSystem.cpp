#include "Scene/System/CameraSystem.hpp"
#include "Engine.hpp"
#include "Scene/Component/Transform.hpp"

using namespace Component;

Component::Camera &CameraSystem::GetActiveCamera()
{
    World &world = Engine::Instance().GetCurrentWorld();

    for (Entity entity: _entities)
    {
        auto &t = world.GetComponent<Camera>(entity);
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
    World &world = Engine::Instance().GetCurrentWorld();
    for (Entity entity: _entities)
    {
        auto &t = world.GetComponent<Camera>(entity);
        t.GetFramebuffer().Delete();
    }
}