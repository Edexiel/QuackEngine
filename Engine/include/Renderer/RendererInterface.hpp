#ifndef _RENDERMANAGER_
#define _RENDERMANAGER_

#include "Scene/System/CameraSystem.hpp"
#include "Scene/System/RenderSystem.hpp"
#include "Scene/System/LightSystem.hpp"

#include <memory>

class World;

namespace Component
{
    class Light;
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
        void UpdateSceneFramebufferEditor(const Maths::Matrix4& projection, const Maths::Matrix4& view, unsigned int idFramebuffer);
        void DrawFramebufferinFramebuffer(const Framebuffer& framebufferDrawIn, const Framebuffer& framebuffer2DrawOut);
        void DrawTextureinFramebuffer(const Framebuffer& framebufferDrawIn, const Texture& textureDrawOut);


        //void AddShaderToUpdate(const Renderer::Shader& shader);
        //void RemoveShaderFromUpdate(const Renderer::Shader& shader);

    };
}

#endif