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
public:
    CameraSystem() = default;

    void Init();
    Component::Camera& GetActiveCamera();
    void Clear();
};

#endif