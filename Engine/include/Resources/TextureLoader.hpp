#ifndef _TEXTURE_LOADER_
#define _TEXTURE_LOADER_

#include <string>

namespace Renderer
{
  struct Texture;
}

namespace Resources
{
    class TextureLoader
    {
    public:

        const char* filePath;
        unsigned int bindTexture;

        unsigned char* data {nullptr};

        int width, height, nrChannels;
        bool antiAliasing;

        TextureLoader(const Renderer::Texture& _bindTexture, const char* _path, bool _antiAliasing = false);
        ~TextureLoader(){};

        static void ReadFile(TextureLoader& textureLoader);
        unsigned int Apply();
    };
}

#endif