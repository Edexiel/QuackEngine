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

    float _scaleAxisX = 0;
    float _scaleAxisY = 0;
    float _scaleAxisZ = 0;

    float _yaw = 0;
    float _pitch = 0;

    float _speedTranslation = 5.0f;
    float _speedRotation = 10.0f;

    void SetScaleAxisX(float scale);
    void SetScaleAxisY(float scale);
    void SetScaleAxisZ(float scale);

    void FreeFly();
    void MouseMovement(const Maths::Vector2d &currentPos, const Maths::Vector2d &oldPos);

    friend SceneWidget;
public:
    CameraEditor(unsigned int width, unsigned int height,
                 float far, float near, float fov);

    void SetInput(Input::InputManager& inputManager);

};

#endif //QUACKENGINE_CAMERAEDITOR_HPP
