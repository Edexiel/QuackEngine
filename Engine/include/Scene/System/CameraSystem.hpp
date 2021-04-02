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
    std::vector<Renderer::Shader> _listShaderToUpdate;

public:
    CameraSystem() = default;

    void Init();
    Component::Camera& GetActiveCamera();
    void Update();
    void Clear();

    void AddShaderToUpdate(const Renderer::Shader& shader);
    void RemoveShaderFromUpdate(const Renderer::Shader& shader);
};


#endif