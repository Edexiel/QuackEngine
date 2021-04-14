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

    void SetAxisScaleX(Entity id, float scale);
    void SetAxisScaleY(Entity id, float scale);
    void SetAxisScaleZ(Entity id, float scale);

public:
    CameraSystem() = default;

    void Init();
    Component::Camera& GetActiveCamera();
    void Update();
    void Clear();

    void AddShaderToUpdate(const Renderer::Shader& shader);
    void RemoveShaderFromUpdate(const Renderer::Shader& shader);

    void SetProjection(Entity id, unsigned int width, unsigned int height, float far, float near, float fov);
    void SetProjection(Entity id, unsigned int width, unsigned int height, float far, float near);

    void CreateView(Entity id);
    void CreateProjection(Entity id);

    void FreeFly(Entity id);

    void Resize(Entity id, unsigned int width, unsigned int height);
};

#endif