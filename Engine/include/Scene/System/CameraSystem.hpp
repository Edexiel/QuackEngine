#ifndef _CAMERASYSTEM_
#define _CAMERASYSTEM_

#include "Scene/Core/System.hpp"
#include "Scene/Component/Camera.hpp"
#include <vector>

namespace Renderer
{
    class Shader;
}

class CameraSystem : public System
{
private:
    void SetScaleAxisX(float scale) const;
    void SetScaleAxisY(float scale) const;
    void SetScaleAxisZ(float scale) const;

    Entity _activeCamera = -1;
    void FreeFly();
    void MouseMovement();
public:
    CameraSystem();

    void InitInput();
    void Update();

    Component::Camera& GetActiveCamera();
    void Clear();
};


#endif