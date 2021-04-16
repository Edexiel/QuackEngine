#ifndef QUACKENGINE_CAMERA_HPP
#define QUACKENGINE_CAMERA_HPP

#include "Maths/Matrix4.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"

#include "Renderer/Framebuffer.hpp"

namespace Input
{
    class InputManager;
};

namespace Component
{
    class Camera
    {
    public:
        bool isActive {true};

    private:
        unsigned int _width;
        unsigned int _height;

        bool _isPerspective{true};

        float _fov;
        float _far;
        float _near;

        Renderer::Framebuffer _framebuffer;

        Maths::Matrix4 _projection;
        Maths::Matrix4 _view;

    public:
        Camera(unsigned int width, unsigned int height, float far, float near, float fov);
        Camera(unsigned int width, unsigned int height, float far, float near);


        void Resize(unsigned int width, unsigned int height);

        Renderer::Framebuffer GetFramebuffer() const;

        const Maths::Matrix4& GetProjection() const;
        const Maths::Matrix4& GetView() const;

        void SetProjection(unsigned int width, unsigned int height, float far, float near,
                           float fov);
        void SetProjection(unsigned int width, unsigned int height, float far, float near);
        void CreateProjection();
        void SetView(const Maths::Matrix4& view);

    };
}
#endif // QUACKENGINE_CAMERA_HPP
