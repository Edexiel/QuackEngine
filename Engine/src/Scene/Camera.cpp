#include "Scene/Camera.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include "Input/InputManager.hpp"

using namespace Scene;
using namespace Maths;

Camera::Camera(const unsigned int width, const unsigned int height,
                      const float far, const float near, const float fov)
:_width{width}, _height{height},_far{far},_near{near},_fov{fov},_isPerspective{true}
{
  _projection = Matrix4::Perspective(_width,_height, _near, _far, _fov);
  _view = Matrix4::Identity();
}

Camera::Camera(const unsigned int width, const unsigned int height,
                      const float far, const float near)
:_width{width}, _height{height},_far{far},_near{near},_fov{0},_isPerspective{false}
{
  _projection = Matrix4::OrthoMatrix(_width,_height, _near, _far);
  _view = Matrix4::Identity();
}

Matrix4 Camera::GetProjection() const
{
  return _projection;
}

Maths::Matrix4 Camera::GetView() const
{
  return _view;
}
void Camera::SetProjection(const unsigned int width, const unsigned int height,
                           const float far, const float near, const float fov)
{
  _width = width;
  _height = height;
  _far = far;
  _near = near;
  _fov = fov;

  _projection = Matrix4::Perspective(_width,_height, _near, _far, _fov);
  _isPerspective = true;
}
void Camera::SetProjection(const unsigned int width, const unsigned int height,
                           const float far, const float near)
{
  _width = width;
  _height = height;
  _far = far;
  _near = near;

  _projection = Matrix4::OrthoMatrix(_width,_height, _near, _far);
  _isPerspective = false;
}
void Camera::CreateProjection()
{
  if(_isPerspective)
    _projection = Matrix4::Perspective(_width,_height, _near, _far, _fov);
  else
    _projection = Matrix4::OrthoMatrix(_width,_height, _near, _far);
}

void Camera::CreateView()
{
  _view = _rotation * Matrix4::Translate(_position);
}

void Camera::SetPosition(const Vector3f &pos)
{
  _position = pos;
}

void Camera::SetRotation(const Quaternion& rot)
{
  _rotation = rot.QuaternionToMatrix();
}

void Camera::SetRotationSpeed(const float speed)
{
  _speedRotation = speed;
}

void Camera::SetTranslationSpeed(const float speed)
{
  _speedTranslation = speed;
}

void Camera::MouseMovement(const Vector2d &currentPos, const Vector2d &oldPos)
{
  Vector2d angleRotation = (oldPos - currentPos) * (_speedRotation * M_PI/ 180.f);
  _yaw += angleRotation.x;
  _pitch = std::clamp(_pitch + angleRotation.y, -M_PI/2.0, M_PI/2.0);

  _rotation = (Quaternion({1,0,0}, _pitch) * Quaternion({0,1,0}, _yaw)).QuaternionToMatrix();
}
void Camera::MoveForward()
{
  _isMovingForward = true;
}
void Camera::MoveBackward()
{
  _isMovingBackward = true;
}
void Camera::MoveRight()
{
  _isMovingRight = true;
}
void Camera::MoveLeft()
{
  _isMovingLeft = true;
}

void Camera::MoveUp()
{
  _isMovingUp = true;
}

void Camera::MoveDown()
{
  _isMovingDown = true;
}

void Camera::Update()
{
  FreeFly();
}
/**
 * Can move the camera in freeFly mode.
 */
void Camera::FreeFly()
{
  Vector3f direction{0,0,0};
  _forward = (_rotation * Vector4f(Vector3f::Backward(), 0)).xyz;
  _right = (_rotation * Vector4f(Vector3f::Left(), 0)).xyz;

  if (_isMovingForward)
    direction = direction + _forward;
  if (_isMovingBackward)
    direction = direction - _forward;
  if (_isMovingLeft)
    direction = direction - _right;
  if (_isMovingRight)
    direction = direction + _right;
  if(_isMovingUp)
    direction = direction + Vector3f::Down();
  if(_isMovingDown)
    direction = direction + Vector3f::Up();

  _position = _position + (direction.Normalize() * _speedTranslation);
}
void Camera::StopMoveForward()
{
  _isMovingForward = false;
}
void Camera::StopMoveBackward()
{
  _isMovingBackward = false;
}
void Camera::StopMoveLeft()
{
  _isMovingLeft = false;
}
void Camera::StopMoveRight()
{
  _isMovingRight = false;
}
void Camera::StopMoveUp()
{
  _isMovingUp = false;
}

void Camera::StopMoveDown()
{
  _isMovingDown = false;
}

void Camera::SetInput(Input::InputManager &inputManager)
{
  inputManager.BindEvent("CameraMoveForward", Input::Key::KEY_W, Input::Action::PRESS);
  inputManager.BindEvent("CameraMoveBackward", Input::Key::KEY_S, Input::Action::PRESS);
  inputManager.BindEvent("CameraMoveRight", Input::Key::KEY_D, Input::Action::PRESS);
  inputManager.BindEvent("CameraMoveLeft", Input::Key::KEY_A, Input::Action::PRESS);

  inputManager.BindEvent("StopCameraMoveForward", Input::Key::KEY_W, Input::Action::RELEASE);
  inputManager.BindEvent("StopCameraMoveBackward", Input::Key::KEY_S, Input::Action::RELEASE);
  inputManager.BindEvent("StopCameraMoveRight", Input::Key::KEY_D, Input::Action::RELEASE);
  inputManager.BindEvent("StopCameraMoveLeft", Input::Key::KEY_A, Input::Action::RELEASE);

  inputManager.RegisterEvent("CameraMoveForward",this, &Scene::Camera::MoveForward);
  inputManager.RegisterEvent("CameraMoveBackward",this, &Scene::Camera::MoveBackward);
  inputManager.RegisterEvent("CameraMoveRight",this, &Scene::Camera::MoveRight);
  inputManager.RegisterEvent("CameraMoveLeft",this, &Scene::Camera::MoveLeft);

  inputManager.RegisterEvent("StopCameraMoveForward",this, &Scene::Camera::StopMoveForward);
  inputManager.RegisterEvent("StopCameraMoveBackward",this, &Scene::Camera::StopMoveBackward);
  inputManager.RegisterEvent("StopCameraMoveRight",this, &Scene::Camera::StopMoveRight);
  inputManager.RegisterEvent("StopCameraMoveLeft",this, &Scene::Camera::StopMoveLeft);
}

