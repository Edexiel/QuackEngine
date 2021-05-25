#ifndef QUACKENGINE_CAMERA_HPP
#define QUACKENGINE_CAMERA_HPP

#include "Scene/Component/ComponentBase.hpp"

#include "Maths/Matrix4.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"

#include "Renderer/Framebuffer.hpp"

namespace Input
{
    class InputManager;
};
class CameraSystem;

namespace Component
{
    class Camera : public ComponentBase
    {
    public:
        bool isActive {true};

        friend ::CameraSystem;
        float _fov {0};
        bool _isPerspective{true};

    private:
        unsigned int _width     {0};
        unsigned int _height    {0};

        float _far {0};
        float _near {0};

        float _scaleAxisX = 0;
        float _scaleAxisY = 0;
        float _scaleAxisZ = 0;

        float _yaw = 0;
        float _pitch = 0;

        float _speedTranslation = 0.1f;
        float _speedRotation = 0.1f;

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
