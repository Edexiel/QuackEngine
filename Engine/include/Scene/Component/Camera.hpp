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

        //todo create a component that move the camera instead of it being inside the class

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

        Maths::Vector3f _position;
    public:
        const Maths::Vector3f &GetPosition() const;

    private:
        Maths::Vector3f _forward{0, 0, -1};
        Maths::Vector3f _right{-1, 0, 0};


        void FreeFly();

        void SetAxisScaleX(float scale);
        void SetAxisScaleY(float scale);
        void SetAxisScaleZ(float scale);


    public:
        //Camera();
        Camera(unsigned int width, unsigned int height, float far, float near, float fov);
        Camera(unsigned int width, unsigned int height, float far, float near);

        ~Camera();

        Renderer::Framebuffer GetFramebuffer() const;

        const Maths::Matrix4& GetProjection() const;
        const Maths::Matrix4& GetView() const;

        void SetProjection(unsigned int width, unsigned int height, float far, float near,
                           float fov);
        void SetProjection(unsigned int width, unsigned int height, float far, float near);
        void CreateProjection();
        void CreateView();

        void SetPosition(const Maths::Vector3f &pos);
        void SetRotation(const Maths::Quaternion &rot);
        void SetRotationSpeed(float speed);

        void SetTranslationSpeed(float speed);
        void MouseMovement(const Maths::Vector2d &currentPos, const Maths::Vector2d &oldPos);
        void SetInput(Input::InputManager &inputManager);


        void Update();
    };
}
#endif // QUACKENGINE_CAMERA_HPP
