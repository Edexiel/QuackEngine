#include "Scene/System/CameraSystem.hpp"
#include "Engine.hpp"
#include "Scene/Component/Transform.hpp"

using namespace Maths;
using namespace Component;
CameraSystem::CameraSystem()
{
    InitInput();
}

Component::Camera& CameraSystem::GetActiveCamera()
{
    World& world = Engine::Instance().GetCurrentWorld();
    for (Entity entity: _entities) {
        auto &t = world.GetComponent<Component::Camera>(entity);
        if (t.isActive)
        {
            _activeCamera = entity;
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

void CameraSystem::SetScaleAxisX(float scale) const
{
    if(_activeCamera < 0)
        return;

    auto &cam = Engine::Instance().GetCurrentWorld().GetComponent<Component::Camera>(_activeCamera);
    cam._scaleAxisX = scale;

    std::cout << "scaleAxisX = " << cam._scaleAxisX << std::endl;
}

void CameraSystem::SetScaleAxisY(float scale) const
{
    if(_activeCamera < 0)
        return;

    auto &cam = Engine::Instance().GetCurrentWorld().GetComponent<Component::Camera>(_activeCamera);
    cam._scaleAxisY = scale;

    std::cout << "scaleAxisY = " << cam._scaleAxisY << std::endl;
}

void CameraSystem::SetScaleAxisZ(float scale) const
{
    if(_activeCamera < 0)
        return;

    auto &cam =Engine::Instance().GetCurrentWorld().GetComponent<Component::Camera>(_activeCamera);
    cam._scaleAxisZ = scale;

    std::cout << "scaleAxisZ = " << cam._scaleAxisZ << std::endl;
}

void CameraSystem::InitInput()
{
    Input::InputManager &inputManager = Engine::Instance().GetInputManager();
    inputManager.RegisterEventAxis("CameraEditorMovementForward",this, &CameraSystem::SetScaleAxisZ);
    inputManager.RegisterEventAxis("CameraEditorMovementRight",this, &CameraSystem::SetScaleAxisX);
    inputManager.RegisterEventAxis("CameraEditorMovementUp",this, &CameraSystem::SetScaleAxisY);
}

void CameraSystem::FreeFly()
{
    if(_activeCamera < 0)
        return;

    World &world = Engine::Instance().GetCurrentWorld();
    auto &cam = world.GetComponent<Component::Camera>(_activeCamera);
    auto &transform = world.GetComponent<Transform>(_activeCamera);

    //todo: faire dans le transform les rotations de forward et right
    transform.forward = (transform.rotation.ToMatrix() * Vector4f(Vector3f::Forward(), 0)).xyz * cam._scaleAxisZ;
    transform.right = (transform.rotation.ToMatrix() * Vector4f(Vector3f::Right(), 0)).xyz * cam._scaleAxisX;
    Vector3f up = Vector3f::Up() * cam._scaleAxisY;
    Vector3f direction = (transform.forward + transform.right + up).GetNormalized();

    transform.position = transform.position + (direction * cam._speedTranslation);
}

void CameraSystem::MouseMovement()
{
    Engine &engine = Engine::Instance();
    World &world = engine.GetCurrentWorld();

    Input::MousePosition &mousePosition = engine.GetInputManager().mousePosition;
    auto &cam = world.GetComponent<Component::Camera>(_activeCamera);
    auto &transform = world.GetComponent<Transform>(_activeCamera);

    Vector2d angleRotation = (mousePosition.prevPos - mousePosition.pos) * (cam._speedRotation * M_PI / 180.f);
    cam._yaw += (float)angleRotation.x;
    cam._pitch = (float)std::clamp(cam._pitch + angleRotation.y, -M_PI / 2.0, M_PI / 2.0);

    transform.rotation = Quaternion({1, 0, 0}, cam._pitch) * Quaternion({0, 1, 0}, cam._yaw);
}

void CameraSystem::Update()
{
    FreeFly();
    MouseMovement();
}