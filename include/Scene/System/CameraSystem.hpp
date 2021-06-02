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
    Entity _activeCamera;
    Engine &_engine;
public:
    CameraSystem();

    Component::Camera& GetActiveCamera();
    void Clear();
};


#endif