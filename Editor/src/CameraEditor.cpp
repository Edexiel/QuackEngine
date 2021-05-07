#include "CameraEditor.hpp"

#include "Input/InputManager.hpp"
#include "Maths/Quaternion.hpp"
#include <algorithm>

using namespace Maths;

void CameraEditor::Update()
{

}

void CameraEditor::SetScaleAxisX(float scale)
{
    _scaleAxisX = scale;
}

void CameraEditor::SetScaleAxisY(float scale)
{
    _scaleAxisY = scale;
}

void CameraEditor::SetScaleAxisZ(float scale)
{
    _scaleAxisX = scale;
}

void CameraEditor::SetInput(Input::InputManager &inputManager)
{
    inputManager.RegisterEventAxis("CameraEditorMovementForward", this, &CameraEditor::SetScaleAxisZ);
    inputManager.RegisterEventAxis("CameraEditorMovementRight", this, &CameraEditor::SetScaleAxisX);
    inputManager.RegisterEventAxis("CameraEditorMovementUp", this, &CameraEditor::SetScaleAxisY);
}

void CameraEditor::FreeFly()
{
    _forward = (_rotation * Vector4f(Vector3f::Backward(), 0)).xyz * _scaleAxisZ;
    _right = (_rotation * Vector4f(Vector3f::Left(), 0)).xyz * _scaleAxisX;
    Vector3f up = Vector3f::Down() * _scaleAxisY;
    Vector3f direction = (_forward + _right + up).GetNormalized();

    _position = _position + (direction * _speedTranslation);
}

void CameraEditor::MouseMovement(const Vector2d &currentPos, const Vector2d &oldPos)
{
    Vector2d angleRotation = (oldPos - currentPos) * (_speedRotation * M_PI / 180.f);
    _yaw += (float) angleRotation.x;
    _pitch = (float) std::clamp(_pitch + angleRotation.y, -M_PI / 2.0, M_PI / 2.0);

    _rotation = (Quaternion({1, 0, 0}, _pitch) * Quaternion({0, 1, 0}, _yaw)).ToMatrix();
}