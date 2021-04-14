#include "Scene/System/CameraSystem.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"

#include "Maths/Matrix4.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"

using namespace Maths;

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
                _listShaderToUpdate[i].SetMatrix4("projection", c.GetProjection());
                _listShaderToUpdate[i].SetMatrix4("view", c.GetView());
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


void CameraSystem::SetProjection(Entity id, const unsigned int width, const unsigned int height,
                           const float far, const float near, const float fov)
{
    auto &camera = World::Instance().GetComponent<Component::Camera>(id);
    camera._width = width;
    camera._height = height;
    camera._far = far;
    camera._near = near;
    camera._fov = fov;

    camera._projection = Matrix4::Perspective(camera._width, camera._height, camera._near, camera._far, camera._fov);
    camera._isPerspective = true;
}

void CameraSystem::SetProjection(Entity id, const unsigned int width, const unsigned int height,
                           const float far, const float near)
{
    auto &camera = World::Instance().GetComponent<Component::Camera>(id);

    camera._width = width;
    camera._height = height;
    camera._far = far;
    camera._near = near;

    camera._projection = Matrix4::OrthoMatrix(camera._width, camera._height, camera._near, camera._far);
    camera._isPerspective = false;
}

void CameraSystem::CreateView(Entity id)
{
    auto &camera = World::Instance().GetComponent<Component::Camera>(id);
    auto &transform = World::Instance().GetComponent<Transform>(id);

    camera._view = transform.GetMatrix();
}

void CameraSystem::CreateProjection(Entity id)
{
    auto &camera = World::Instance().GetComponent<Component::Camera>(id);

    if (camera._isPerspective)
        camera._projection = Matrix4::Perspective(camera._width, camera._height, camera._near, camera._far, camera._fov);
    else
        camera._projection = Matrix4::OrthoMatrix(camera._width, camera._height, camera._near, camera._far);
}

void CameraSystem::Resize(Entity id, unsigned int width, unsigned int height)
{
    auto &camera = World::Instance().GetComponent<Component::Camera>(id);
    camera._width = width;
    camera._height = height;

    //_framebuffer.Resize(width, height);

    if (camera._isPerspective)
        camera._projection = Matrix4::Perspective(camera._width, camera._height, camera._near, camera._far, camera._fov);
    else
        camera._projection = Matrix4::OrthoMatrix(camera._width, camera._height, camera._near, camera._far);
}

void CameraSystem::SetAxisScaleX(Entity id, float scale)
{
    auto &camera = World::Instance().GetComponent<Component::Camera>(id);
    camera._axisScaleX = scale;
}

void CameraSystem::SetAxisScaleY(Entity id, float scale)
{
    auto &camera = World::Instance().GetComponent<Component::Camera>(id);
    camera._axisScaleY = scale;
}

void CameraSystem::SetAxisScaleZ(Entity id, float scale)
{
    auto &camera = World::Instance().GetComponent<Component::Camera>(id);
    camera._axisScaleY = scale;
}

void CameraSystem::FreeFly(Entity id)
{
    auto &camera = World::Instance().GetComponent<Component::Camera>(id);
    auto &transform = World::Instance().GetComponent<Transform>(id);

    camera._forward = (camera._rotation * Vector4f(Vector3f::Forward(), 0)).xyz * camera._axisScaleZ;
    camera._right = (camera._rotation * Vector4f(Vector3f::Right(), 0)).xyz * camera._axisScaleX;
    Vector3f up = Vector3f::Up() * camera._axisScaleY;
    Vector3f direction = (camera._forward + camera._right + up).GetNormalized();

    transform.position = transform.position + (direction * camera._speedTranslation);
}
