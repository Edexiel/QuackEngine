#ifndef _RENDERMANAGER_
#define _RENDERMANAGER_

#include <memory>

class World;

namespace Maths
{
    struct Matrix4;
}

namespace Renderer
{
    class Framebuffer;

    class Texture;

    struct RendererInterface
    {

        RendererInterface() = default;
        ~RendererInterface() = default;

        static Framebuffer GetSceneUpdatedFramebuffer();
        static void UpdateSceneFramebufferEditor(const Maths::Matrix4 &projection, const Maths::Matrix4 &view,
                                          const Framebuffer &framebuffer);
        static void DrawFramebufferinFramebuffer(const Framebuffer &framebufferDrawIn, const Framebuffer &framebufferDrawOut);
        static void DrawTextureinFramebuffer(const Framebuffer &framebufferDrawIn, const Texture &textureDrawOut);


        //void AddShaderToUpdate(const Renderer::Shader& shader);
        //void RemoveShaderFromUpdate(const Renderer::Shader& shader);

    };
}

#endif