#ifndef QUACKENGINE_CAMERAEDITOR_HPP
#define QUACKENGINE_CAMERAEDITOR_HPP

#include "Maths/Vector3.hpp"
#include "Maths/Matrix4.hpp"

namespace Input
{
  class InputManager;
};
class CameraEditor
{
private:
    Maths::Vector3f _position;
    Maths::Matrix4 _rotation;

    Maths::Vector3f _forward;
    Maths::Vector3f _right;

    float _scaleAxisX = 0;
    float _scaleAxisY = 0;
    float _scaleAxisZ = 0;

    float _yaw = 0;
    float _pitch = 0;

    float _speedTranslation = 0.01f;
    float _speedRotation = 0.01f;

    void SetScaleAxisX(float scale);
    void SetScaleAxisY(float scale);
    void SetScaleAxisZ(float scale);

    void FreeFly();
    void MouseMovement(const Maths::Vector2d &currentPos, const Maths::Vector2d &oldPos);
public:
    void Update();
    void SetInput(Input::InputManager& inputManager);

};

#endif //QUACKENGINE_CAMERAEDITOR_HPP
