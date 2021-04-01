#ifndef _RENDERMANAGER_
#define _RENDERMANAGER_

#include "Scene/System/CameraSystem.hpp"
#include "Scene/System/RenderSystem.hpp"
#include "Scene/System/LightSystem.hpp"

#include "Renderer/Mesh.hpp"
#include "Renderer/Shader.hpp"

#include "Renderer/Window.hpp"

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
        std::shared_ptr<RenderSystem>   _renderSystem;
        std::shared_ptr<CameraSystem>   _cameraSystem;
        std::shared_ptr<LightSystem>    _lightSystem;

        Shader _shader;
        Mesh _quadMesh;

        Window _window;

    public:
        RendererManager() = default;

        void Init(World* world);
        void InitWindow(unsigned int width, unsigned int height, const char* name);

        void Clear();

        Window GetWindow() const;

        void Update();

        void AddShaderToUpdate(const Renderer::Shader& shader);
        void RemoveShaderFromUpdate(const Renderer::Shader& shader);

    private:
        Framebuffer GetCameraFrame(Component::Camera& camera);
    };
}

#endif