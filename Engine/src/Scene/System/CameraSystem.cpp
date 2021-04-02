#include "Scene/System/CameraSystem.hpp"
#include "Scene/Core/World.hpp"

void CameraSystem::Init()
{

}

Component::Camera& CameraSystem::GetActiveCamera()
{
    for (Entity entity: _entities) {
        auto &t = World::Instance().GetComponent<Component::Camera>(entity);
        if (t.isActive)
            return t;
    }
    Assert_Fatal_Error(true, "No Camera Active");
    //exit(-1);
}

void CameraSystem::Clear()
{
    for (Entity entity: _entities)
    {
        auto &t = World::Instance().GetComponent<Component::Camera>(entity);
        t.GetFramebuffer().Delete();
    }
}