#include "CameraEditor.hpp"

#include "Renderer/RendererPlatform.hpp"
#include "Input/InputManager.hpp"
#include "Maths/Quaternion.hpp"

#include "Engine.hpp"
#include <algorithm>
#include "Engine.hpp"

using namespace Maths;

CameraEditor::CameraEditor(unsigned int width, unsigned int height,
             float far, float near, float fov)
             : _width{width}, _height{height}, _far{far}, _near{near}, _fov{fov}, _isPerspective{true},
             _framebuffer{Renderer::RendererPlatform::CreateFramebuffer(width, height)}{}

void CameraEditor::SetRightScale(float scale)
{
    _rightScale = scale;
}

void CameraEditor::SetLeftScale(float scale)
{
    _leftScale = scale;
}

void CameraEditor::SetForwardScale(float scale)
{
    _forwardScale = scale;
}

void CameraEditor::SetBackwardScale(float scale)
{
    _backwardScale = scale;
}

void CameraEditor::SetUpScale(float scale)
{
    _upScale = scale;
}

void CameraEditor::SetDownScale(float scale)
{
    _downScale = scale;
}

void CameraEditor::SetInput()
{
    Input::InputManager& inputManager = Engine::Instance().GetInputManager();
    inputManager.RegisterEventAxis("CameraEditorMovementForward", this, &CameraEditor::SetForwardScale);
    inputManager.RegisterEventAxis("CameraEditorMovementBackward", this, &CameraEditor::SetBackwardScale);
    inputManager.RegisterEventAxis("CameraEditorMovementRight", this, &CameraEditor::SetRightScale);
    inputManager.RegisterEventAxis("CameraEditorMovementLeft", this, &CameraEditor::SetLeftScale);
    inputManager.RegisterEventAxis("CameraEditorMovementUp", this, &CameraEditor::SetUpScale);
    inputManager.RegisterEventAxis("CameraEditorMovementDown", this, &CameraEditor::SetDownScale);
}

void CameraEditor::FreeFly()
{
    Vector3f forward = _rotation * Vector3f::Forward() * (_forwardScale + _backwardScale);
    Vector3f right = _rotation * Vector3f::Right() * (_rightScale + _leftScale);

    Vector3f up = Vector3f::Up() * (_upScale + _downScale);
    Vector3f direction = (forward + right + up).GetNormalized();

    _position = _position + (direction * _speedTranslation) * Engine::Instance().GetTimeManager().GetDeltaTime();
}

void CameraEditor::MouseMovement(const Vector2d &currentPos, const Vector2d &oldPos)
{
    Vector2d angleRotation = (currentPos - oldPos) * (_speedRotation * Pi<float>() / 180.f);
    float deltatime = (float)Engine::Instance().GetDeltaTime();
    _yaw += (float)angleRotation.x;
    _pitch = (float)std::clamp(_pitch + angleRotation.y, -Pi<float>() / 2.0, Pi<float>() / 2.0);
    _rotation = Quaternion({0, 1, 0}, _yaw) * Quaternion({1, 0, 0}, _pitch);
}


