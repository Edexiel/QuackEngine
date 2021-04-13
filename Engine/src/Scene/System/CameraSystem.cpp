#include "Scene/System/CameraSystem.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"

Component::Camera& CameraSystem::GetActiveCamera()
{
    for (Entity entity: _entities) {
        auto &t = World::Instance().GetComponent<Component::Camera>(entity);
        if (t.isActive)
            return t;
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

void CameraSystem::Update()
{
    for (Entity entity: _entities)
    {
        auto &c = World::Instance().GetComponent<Component::Camera>(entity);
        if (c.isActive)
        {
            for (unsigned int i = 0; i < _listShaderToUpdate.size() ; i++)
            {
                _listShaderToUpdate[i].Use();

                _listShaderToUpdate[i].SetMatrix4("projection", c.GetProjection());
                _listShaderToUpdate[i].SetMatrix4("view", c.GetView());;
            }
        }
    }
}

void CameraSystem::Init()
{
    for (Entity entity: _entities)
    {
        auto &c = World::Instance().GetComponent<Component::Camera>(entity);
        if(c.isActive)
        {
            c.SetInput(*World::Instance().GetInputManager().get());
            return;
        }
    }
}

void CameraSystem::AddShaderToUpdate(const Renderer::Shader& shader)
{
    _listShaderToUpdate.push_back(shader);
}

void CameraSystem::RemoveShaderFromUpdate(const Renderer::Shader& shader)
{
    for (unsigned int i = 0; i < _listShaderToUpdate.size(); i++)
    {
        if (_listShaderToUpdate[i].GetID() == shader.GetID())
        {
            _listShaderToUpdate.erase(_listShaderToUpdate.cbegin() + i);
            return;
        }
    }
}
