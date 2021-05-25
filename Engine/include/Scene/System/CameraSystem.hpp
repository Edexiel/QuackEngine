#ifndef _CAMERASYSTEM_
#define _CAMERASYSTEM_

#include "Scene/Core/System.hpp"
#include "Scene/Component/Camera.hpp"
#include <vector>

namespace Renderer
{
    class Shader;
}
class Engine;

class CameraSystem : public System
{
private:
    void SetScaleAxisX(float scale) const;
    void SetScaleAxisY(float scale) const;
    void SetScaleAxisZ(float scale) const;

    Entity _activeCamera;
    Engine &_engine;
    void FreeFly() const;
    void MouseMovement() const;
    void UpdateCameraAngle() const;
public:
    CameraSystem();

    void InitInput();
    void Update();
    Component::Camera& GetActiveCamera();
    void Clear();

    bool _isFreeFlyCam{false};
};


#endif