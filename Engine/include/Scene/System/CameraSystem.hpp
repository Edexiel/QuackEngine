#ifndef _CAMERASYSTEM_
#define _CAMERASYSTEM_

#include "Scene/Core/System.hpp"
#include "Scene/Component/Camera.hpp"

class CameraSystem : public System
{
private:
    
public:
    CameraSystem() = default;

    Component::Camera& GetActiveCamera();
    void Clear();
};


#endif