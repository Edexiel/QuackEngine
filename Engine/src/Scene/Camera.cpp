#include "Scene/Camera.hpp"

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

void Camera::CreateProjection()
{
  if(_isPerspective)
    _projection = Matrix4::Perspective(_width,_height, _near, _far, _fov);
  else
    _projection = Matrix4::OrthoMatrix(_width,_height, _near, _far);
}

void Camera::CreateView()
{
  _view = _rotation.QuaternionToMatrix() * Matrix4::Translate(_position);
}

void Camera::SetPosition(const Vector3f &pos)
{
  _position = pos;
}

void Camera::SetRotation(const Quaternion& rot)
{
  _rotation = rot;
}

void Camera::SetRotationSpeed(const float speed)
{
  _speedRotation = speed;
}

void Camera::MouseMovement(const Vector2d &currentPos, const Vector2d &oldPos)
{
  Vector2d newAngle = (currentPos - oldPos) * (_speedRotation * 3.14f / 180.f);
  _rotation = _rotation * Quaternion({0,1,0}, newAngle.x) * Quaternion({1,0,0}, newAngle.y);
}
