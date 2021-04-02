#ifndef _CAMERASYSTEM_
#define _CAMERASYSTEM_

#include "Scene/Core/System.hpp"
#include "Scene/Component/Camera.hpp"

class CameraSystem : public System
{
private:
    
public:
    CameraSystem() = default;

    void Init();
    Component::Camera& GetActiveCamera();
    void Update();
    void Init();
    void Clear();
};


#endif