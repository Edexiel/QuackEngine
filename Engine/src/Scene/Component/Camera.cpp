#include "Scene/Component/Camera.hpp"

#define _USE_MATH_DEFINES

#include <math.h>
#include <algorithm>

#include "Input/InputManager.hpp"

#include "Scene/Core/World.hpp"

using namespace Component;
using namespace Maths;

/*Camera::Camera()
{
    _framebuffer = Renderer::Framebuffer::LoadFramebuffer(_width, _height);
}*/

Camera::Camera(const unsigned int width, const unsigned int height,
               const float far, const float near, const float fov)
        : _width{width}, _height{height}, _far{far}, _near{near}, _fov{fov}, _isPerspective{true},
          _framebuffer{Renderer::Framebuffer::LoadFramebuffer(width, height)}
{
    _projection = Matrix4::Perspective(_width, _height, _near, _far, _fov);
    _view = Matrix4::Identity();
}

Camera::Camera(const unsigned int width, const unsigned int height,
               const float far, const float near)
        : _width{width}, _height{height}, _far{far}, _near{near}, _fov{0}, _isPerspective{false},
          _framebuffer{Renderer::Framebuffer::LoadFramebuffer(width, height)}
{
    _projection = Matrix4::OrthoMatrix(_width, _height, _near, _far);
    _view = Matrix4::Identity();
}

Camera::~Camera()
{}

Renderer::Framebuffer Camera::GetFramebuffer() const
{
    return _framebuffer;
}



const Matrix4& Camera::GetProjection() const
{
    return _projection;
}

const Maths::Matrix4& Camera::GetView() const
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

    _projection = Matrix4::Perspective(_width, _height, _near, _far, _fov);
    _isPerspective = true;
}

void Camera::SetProjection(const unsigned int width, const unsigned int height,
                           const float far, const float near)
{
    _width = width;
    _height = height;
    _far = far;
    _near = near;

    _projection = Matrix4::OrthoMatrix(_width, _height, _near, _far);
    _isPerspective = false;
}

void Camera::CreateProjection()
{
    if (_isPerspective)
        _projection = Matrix4::Perspective(_width, _height, _near, _far, _fov);
    else
        _projection = Matrix4::OrthoMatrix(_width, _height, _near, _far);
}

void Camera::CreateView()
{
    _view = _rotation * Matrix4::Translate(_position);
}

void Camera::SetPosition(const Vector3f &pos)
{
    _position = pos;
}

void Camera::SetRotation(const Quaternion &rot)
{
    _rotation = rot.ToMatrix();
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
    Vector2d angleRotation = (oldPos - currentPos) * (_speedRotation * M_PI / 180.f);
    _yaw += angleRotation.x;
    _pitch = std::clamp(_pitch + angleRotation.y, -M_PI / 2.0, M_PI / 2.0);

    _rotation = (Quaternion({1, 0, 0}, _pitch) * Quaternion({0, 1, 0}, _yaw)).ToMatrix();
}


void Camera::Update()
{
    FreeFly();
//    std::cout << "pos.x = " << _position.x << ", pos.y = " << _position.y << ", pos.z = " << _position.z << std::endl;
}

/**
 * Can move the camera in freeFly mode.
 */
void Camera::FreeFly()
{
    _forward = (_rotation * Vector4f(Vector3f::Forward(), 0)).xyz * _axisScaleZ;
    _right = (_rotation * Vector4f(Vector3f::Right(), 0)).xyz * _axisScaleX;
    Vector3f up = Vector3f::Up() * _axisScaleY;
    Vector3f direction = (_forward + _right + up).GetNormalized();

    _position = _position + (direction * _speedTranslation);
}


void Camera::SetInput(Input::InputManager &inputManager)
{
    std::cout << "SetInput\n";
    inputManager.RegisterEventAxis("CameraMovementForwardAxis", this, &Camera::SetAxisScaleZ);
    inputManager.RegisterEventAxis("CameraMovementRightAxis", this, &Camera::SetAxisScaleX);
    inputManager.RegisterEventAxis("CameraMovementUpAxis", this, &Camera::SetAxisScaleY);
}

void Camera::SetAxisScaleX(const float scale)
{
    _axisScaleX = scale;
    std::cout << "_axisScaleX = " << _axisScaleX << std::endl;
}

void Camera::SetAxisScaleY(const float scale)
{
    _axisScaleY = scale;
    std::cout << "_axisScaleY = " << _axisScaleY << std::endl;
}

void Camera::SetAxisScaleZ(const float scale)
{
    _axisScaleZ = scale;
    std::cout << "_axisScaleZ = " << _axisScaleZ << std::endl;
}

const Vector3f &Camera::GetPosition() const
{
    return _position;
}

void Camera::Resize(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;

    //_framebuffer.Resize(width, height);

    if (_isPerspective)
        _projection = Matrix4::Perspective(_width, _height, _near, _far, _fov);
    else
        _projection = Matrix4::OrthoMatrix(_width, _height, _near, _far);
}
