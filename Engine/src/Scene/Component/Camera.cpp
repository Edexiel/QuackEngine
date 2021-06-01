#include "Scene/Component/Camera.hpp"
#include "Engine.hpp"

using namespace Component;
using namespace Maths;

Camera::Camera(const unsigned int width, const unsigned int height,
               const float far, const float near, const float fov = 0)
        : _width{width}, _height{height}, _far{far}, _near{near}, _fov{fov},
          _framebuffer{Renderer::Framebuffer::LoadFramebuffer(width, height)}
{
    if(fov == 0.0f)
    {
        _projection = Matrix4::OrthoMatrix(_width, _height, _near, _far);
        _isPerspective = false;
    }
    else
    {
        _projection = Matrix4::Perspective(_width, _height, _near, _far, fov);
        _isPerspective = true;
    }
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

void Camera::LoadFramebuffer()
{
    Maths::Vector2i size = Engine::Instance().GetWindowSize();
    _framebuffer = Renderer::Framebuffer::LoadFramebuffer(size.x, size.y);
}
