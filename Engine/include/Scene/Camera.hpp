#ifndef QUACKENGINE_CAMERA_HPP
#define QUACKENGINE_CAMERA_HPP

#include "Maths/Matrix4.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"

namespace Scene
{

class Camera
{
private:
  unsigned int   _width;
  unsigned int   _height;

  float          _fov;
  float          _far;
  float          _near;
  float          _speedRotation{0};
  float          _speedTranslation{0};

  bool           _isPerspective    = false;
  bool           _isMovingForward  = false;
  bool           _isMovingBackward = false;
  bool           _isMovingLeft     = false;
  bool           _isMovingRight    = false;

  Maths::Matrix4 _projection;
  Maths::Matrix4 _view;

  Maths::Vector3f _position;
  Maths::Vector3f _forward{0,0,-1};
  Maths::Vector3f _right{-1,0,0};
  Maths::Vector2d _angleRotation{0,0};
  Maths::Quaternion _rotation;

  void Move();


public:
  Camera(const unsigned int width, const unsigned int height, const float far, const float near, const float fov);
  Camera(const unsigned int width, const unsigned int height, const float far, const float near);

  Maths::Matrix4 GetProjection() const;
  Maths::Matrix4 GetView() const;

  void CreateProjection();
  void CreateView();

  void SetPosition(const Maths::Vector3f& pos);
  void SetRotation(const Maths::Quaternion& rot);
  void SetRotationSpeed(const float speed);
  void SetTranslationSpeed(const float speed);

  void MouseMovement(const Maths::Vector2d& currentPos, const Maths::Vector2d& oldPos);
  void MoveForward();
  void MoveBackward();
  void MoveLeft();
  void MoveRight();
  void StopMoveForward();
  void StopMoveBackward();
  void StopMoveLeft();
  void StopMoveRight();

  void Update();
};
}
#endif // QUACKENGINE_CAMERA_HPP
