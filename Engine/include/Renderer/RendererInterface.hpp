#ifndef _RENDERMANAGER_
#define _RENDERMANAGER_

#include "Scene/System/CameraSystem.hpp"
#include "Scene/System/RenderSystem.hpp"
#include "Scene/System/LightSystem.hpp"

#include "Scene/Component/Model.hpp"

//#include "Renderer/Mesh.hpp"
//#include "Renderer/Shader.hpp"


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
    struct RendererInterface
    {
        std::shared_ptr<RenderSystem>   renderSystem;
        std::shared_ptr<CameraSystem>   cameraSystem;
        std::shared_ptr<LightSystem>    lightSystem;

        RendererInterface() = default;
        ~RendererInterface() = default;

        void Set(std::shared_ptr<RenderSystem> _renderSystem, std::shared_ptr<CameraSystem> _cameraSystem, std::shared_ptr<LightSystem> _lightSystem);

        Framebuffer GetSceneUpdatedFramebuffer();
        void DrawFramebufferinFrambuffer(const Framebuffer& framebufferDrawIn, const Framebuffer& framebuffer2DrawOut);
        void DrawTextureinFramebuffer(const Framebuffer& framebufferDrawIn, const Texture& textureDrawOut);


        //void AddShaderToUpdate(const Renderer::Shader& shader);
        //void RemoveShaderFromUpdate(const Renderer::Shader& shader);

    };
}

#endif