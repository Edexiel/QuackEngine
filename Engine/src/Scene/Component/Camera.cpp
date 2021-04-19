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

/*
void Camera::MouseMovement(const Vector2d &currentPos, const Vector2d &oldPos)
{
    Vector2d angleRotation = (oldPos - currentPos) * (_speedRotation * M_PI / 180.f);
    _yaw += angleRotation.x;
    _pitch = std::clamp(_pitch + angleRotation.y, -M_PI / 2.0, M_PI / 2.0);

    _rotation = (Quaternion({1, 0, 0}, _pitch) * Quaternion({0, 1, 0}, _yaw)).ToMatrix();
}

void Camera::SetInput(Input::InputManager &inputManager)
{
    std::cout << "SetInput\n";
    inputManager.RegisterEventAxis("CameraMovementForwardAxis", this, &Camera::SetAxisScaleZ);
    inputManager.RegisterEventAxis("CameraMovementRightAxis", this, &Camera::SetAxisScaleX);
    inputManager.RegisterEventAxis("CameraMovementUpAxis", this, &Camera::SetAxisScaleY);
}
*/