#include "Scene/System/CameraSystem.hpp"
#include "Engine.hpp"

using namespace Maths;
using namespace Component;
CameraSystem::CameraSystem(): _engine{Engine::Instance()}
{
    InitInput();
}

Component::Camera& CameraSystem::GetActiveCamera()
{
    World& world = _engine.GetCurrentWorld();
    for (Entity entity: _entities) {
        auto &t = world.GetComponent<Component::Camera>(entity);
        if (t.isActive)
        {
            _activeCamera = entity;
            Transform trs = world.GetComponent<Transform>(entity);
            trs.scale.z *= -1;
            t.SetView(trs.GetMatrix().GetInvert());
            return t;
        }
    }
    Assert_Fatal_Error(true, "No Camera Active");
    exit(-1);
}

void CameraSystem::Clear()
{
    World &world = _engine.GetCurrentWorld();
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

    auto &cam = _engine.GetCurrentWorld().GetComponent<Component::Camera>(_activeCamera);
    cam._scaleAxisX = scale;
}

void CameraSystem::SetScaleAxisY(float scale) const
{
    if(_activeCamera < 0)
        return;

    auto &cam = _engine.GetCurrentWorld().GetComponent<Component::Camera>(_activeCamera);
    cam._scaleAxisY = scale;
}

void CameraSystem::SetScaleAxisZ(float scale) const
{
    if(_activeCamera < 0)
        return;

    auto &cam =_engine.GetCurrentWorld().GetComponent<Component::Camera>(_activeCamera);
    cam._scaleAxisZ = scale;
}

void CameraSystem::InitInput()
{
    Input::InputManager &inputManager = _engine.GetInputManager();
    inputManager.RegisterEventAxis("CameraEditorMovementForward",this, &CameraSystem::SetScaleAxisZ);
    inputManager.RegisterEventAxis("CameraEditorMovementRight",this, &CameraSystem::SetScaleAxisX);
    inputManager.RegisterEventAxis("CameraEditorMovementUp",this, &CameraSystem::SetScaleAxisY);
}

void CameraSystem::FreeFly() const
{
    if(_activeCamera < 0)
        return;

    World &world = _engine.GetCurrentWorld();
    auto &cam = world.GetComponent<Component::Camera>(_activeCamera);
    auto &transform = world.GetComponent<Transform>(_activeCamera);

    Vector3f forward = transform.rotation * Vector3f::Forward() * cam._scaleAxisZ;
    Vector3f right = transform.rotation * Vector3f::Right() * cam._scaleAxisX;

    Vector3f up = Vector3f::Down() * cam._scaleAxisY;
    Vector3f direction = (forward + right + up).GetNormalized();

    transform.position = transform.position + (direction * cam._speedTranslation);
}

void CameraSystem::MouseMovement() const
{
    World &world = _engine.GetCurrentWorld();

    Input::MousePosition &mousePosition = _engine.GetInputManager().mousePosition;
    auto &cam = world.GetComponent<Component::Camera>(_activeCamera);
    auto &transform = world.GetComponent<Transform>(_activeCamera);
    Vector3f eulerRot = transform.rotation.ToEuler();

    Vector2d angleRotation = (mousePosition.prevPos - mousePosition.pos) * (cam._speedRotation * M_PI / 180.f);
    cam._yaw -= (float)angleRotation.x;
    cam._pitch = (float)std::clamp(cam._pitch - angleRotation.y, -M_PI / 2.0, M_PI / 2.0);

    transform.rotation = Quaternion({0, 1, 0}, cam._yaw) * Quaternion({1, 0, 0}, cam._pitch);
}

void CameraSystem::UpdateCameraAngle() const
{
    World &world = _engine.GetCurrentWorld();

    auto &cam = world.GetComponent<Component::Camera>(_activeCamera);
    auto &transform = world.GetComponent<Transform>(_activeCamera);
    Vector3f eulerRot = transform.rotation.ToEuler();
    cam._yaw = eulerRot.y;
    cam._pitch = eulerRot.x;
}

void CameraSystem::Update()
{
    if(_isFreeFlyCam)
    {
        MouseMovement();
        FreeFly();
    }
    else
    {
        UpdateCameraAngle();
    }

}