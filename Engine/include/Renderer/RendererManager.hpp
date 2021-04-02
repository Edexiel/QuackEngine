#ifndef _RENDERMANAGER_
#define _RENDERMANAGER_

#include "Scene/System/CameraSystem.hpp"
#include "Scene/System/RenderSystem.hpp"
#include "Scene/System/LightSystem.hpp"

#include "Renderer/Mesh.hpp"
#include "Renderer/Shader.hpp"


#include <memory>

class World;

namespace Component
{
    class Light;
    class Model;
    class Camera;
}

namespace Renderer
{
    class RendererManager
    {
        World* _world {nullptr};

        Shader _shader;
        Mesh _quadMesh;

    public:

        std::shared_ptr<RenderSystem>   _renderSystem;
        std::shared_ptr<CameraSystem>   _cameraSystem;
        std::shared_ptr<LightSystem>    _lightSystem;

        RendererManager() = default;

        void Init(World* world);

        void Clear();

        void Update();

        void AddShaderToUpdate(const Renderer::Shader& shader);
        void RemoveShaderFromUpdate(const Renderer::Shader& shader);

    private:
        Framebuffer GetCameraFrame(Component::Camera& camera);
    };
}

#endif