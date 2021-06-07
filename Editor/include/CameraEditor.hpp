#ifndef QUACKENGINE_CAMERAEDITOR_HPP
#define QUACKENGINE_CAMERAEDITOR_HPP

#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"
#include "Maths/Matrix4.hpp"
#include "Renderer/Framebuffer.hpp"

namespace Input
{
  class InputManager;
};
class SceneWidget;
class CameraEditor
{
private:
    Maths::Vector3f _position{0.f, 0.f,-5.f};
    Maths::Quaternion _rotation;

    Renderer::Framebuffer _framebuffer;

    unsigned int _width;
    unsigned int _height;

    bool _isPerspective{true};

    float _far;
    float _near;
    float _fov;

    float _rightScale = 0;
    float _leftScale = 0;
    float _forwardScale = 0;
    float _backwardScale = 0;
    float _upScale = 0;
    float _downScale = 0;

    float _yaw = 0;
    float _pitch = 0;

    float _speedTranslation = 5.0f;
    float _speedRotation = 0.1f;

    void SetRightScale(float scale);
    void SetLeftScale(float scale);
    void SetForwardScale(float scale);
    void SetBackwardScale(float scale);
    void SetUpScale(float scale);
    void SetDownScale(float scale);

    void FreeFly();
    void MouseMovement(const Maths::Vector2d &currentPos, const Maths::Vector2d &oldPos);

    friend SceneWidget;
public:
    CameraEditor(unsigned int width, unsigned int height,
                 float far, float near, float fov);

    void SetInput();

};

#endif //QUACKENGINE_CAMERAEDITOR_HPP
