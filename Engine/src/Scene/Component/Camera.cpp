#include "Scene/Component/Camera.hpp"

#define _USE_MATH_DEFINES

#include <math.h>
#include <algorithm>

#include "Input/InputManager.hpp"

#include "Scene/Core/World.hpp"

using namespace Component;
using namespace Maths;

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

void Camera::SetView(const Matrix4 &view)
{
    _view = view;
}
