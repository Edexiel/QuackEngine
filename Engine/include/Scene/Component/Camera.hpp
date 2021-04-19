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

class CameraSystem;

namespace Component
{
    class Camera
    {
    private:
        bool isActive {true};

        unsigned int _width;
        unsigned int _height;

        bool _isPerspective{true};

        float _fov;
        float _far;
        float _near;

        friend class ::CameraSystem;

        Renderer::Framebuffer _framebuffer;

        float _speedRotation{0.01};
        float _speedTranslation{0.01};

        double _pitch{0};
        double _yaw{0};

        float _axisScaleX{0};
        float _axisScaleY{0};
        float _axisScaleZ{0};

        Maths::Matrix4 _projection;
        Maths::Matrix4 _rotation;// todo: check what is better between Quaternion and Matrix for the rotation.
        Maths::Matrix4 _view;

        Maths::Vector3f _forward;
        Maths::Vector3f _right;


    public:
        //Camera();
        Camera(unsigned int width, unsigned int height, float far, float near, float fov);
        Camera(unsigned int width, unsigned int height, float far, float near);

        ~Camera();

        Renderer::Framebuffer GetFramebuffer() const;

        const Maths::Matrix4& GetProjection() const;
        const Maths::Matrix4& GetView() const;


       //void Update();
    };
}
#endif // QUACKENGINE_CAMERA_HPP
