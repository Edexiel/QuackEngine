#ifndef _RENDERMANAGER_
#define _RENDERMANAGER_

#include <memory>

#include "Maths/Matrix4.hpp"

class World;

namespace Renderer
{
    class Framebuffer;
    class Texture;

    struct RendererInterface
    {

        RendererInterface() = default;
        ~RendererInterface() = default;

        Framebuffer GetSceneUpdatedFramebuffer();
        void UpdateSceneFramebufferEditor(const Maths::Matrix4& projection, const Maths::Matrix4& view, Framebuffer& framebuffer);
        void DrawFramebufferinFramebuffer(const Framebuffer& framebufferDrawIn, const Framebuffer& framebufferDrawOut);
        void DrawTextureinFramebuffer(const Framebuffer& framebufferDrawIn, const Texture& textureDrawOut);


        //void AddShaderToUpdate(const Renderer::Shader& shader);
        //void RemoveShaderFromUpdate(const Renderer::Shader& shader);

    };
}

#endif