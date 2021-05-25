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
        RenderSystem*   renderSystem;
        CameraSystem*   cameraSystem;
        LightSystem*    lightSystem;

        RendererInterface() = default;
        ~RendererInterface() = default;

        void Set(RenderSystem* _renderSystem, CameraSystem* _cameraSystem, LightSystem* _lightSystem);

        Framebuffer GetSceneUpdatedFramebuffer();
        void UpdateSceneFramebufferEditor(const Maths::Matrix4& projection, const Maths::Matrix4& view, Framebuffer& framebuffer);
        void DrawFramebufferinFramebuffer(const Framebuffer& framebufferDrawIn, const Framebuffer& framebufferDrawOut);
        void DrawTextureinFramebuffer(const Framebuffer& framebufferDrawIn, const Texture& textureDrawOut);


        //void AddShaderToUpdate(const Renderer::Shader& shader);
        //void RemoveShaderFromUpdate(const Renderer::Shader& shader);

    };
}

#endif