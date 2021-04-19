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
    std::cout << "SetScaleAxisX: "<< _scaleAxisX << std::endl;
}

void CameraEditor::SetScaleAxisY(float scale)
{
    _scaleAxisY = scale;
    std::cout << "SetScaleAxisY: "<< _scaleAxisY << std::endl;
}

void CameraEditor::SetScaleAxisZ(float scale)
{
    _scaleAxisX = scale;
    std::cout << "SetScaleAxisZ: "<< _scaleAxisZ << std::endl;
}

void CameraEditor::SetInput(Input::InputManager &inputManager)
{
    inputManager.RegisterEventAxis("CameraEditorMovementForward",this, &CameraEditor::SetScaleAxisZ);
    inputManager.RegisterEventAxis("CameraEditorMovementRight",this, &CameraEditor::SetScaleAxisX);
    inputManager.RegisterEventAxis("CameraEditorMovementUp",this, &CameraEditor::SetScaleAxisY);
}

void CameraEditor::FreeFly()
{
    _forward = (_rotation * Vector4f(Vector3f::Forward(), 0)).xyz * _scaleAxisZ;
    _right = (_rotation * Vector4f(Vector3f::Right(), 0)).xyz * _scaleAxisX;
    Vector3f up = Vector3f::Up() * _scaleAxisY;
    Vector3f direction = (_forward + _right + up).GetNormalized();

    _position = _position + (direction * _speedTranslation);
}

void CameraEditor::MouseMovement(const Vector2d &currentPos, const Vector2d &oldPos)
{
    Vector2d angleRotation = (oldPos - currentPos) * (_speedRotation * M_PI / 180.f);
    _yaw += angleRotation.x;
    _pitch = std::clamp(_pitch + angleRotation.y, -M_PI / 2.0, M_PI / 2.0);

    _rotation = (Quaternion({1, 0, 0}, _pitch) * Quaternion({0, 1, 0}, _yaw)).ToMatrix();
}