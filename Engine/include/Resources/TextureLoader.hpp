#ifndef _TEXTURE_LOADER_
#define _TEXTURE_LOADER_

#include <string>

namespace Resources
{

    class TextureLoader
    {
    private:

        const char* filePath;
        unsigned int bindTexture;

        unsigned char* data {nullptr};

        int width, height, nrChannels;
        bool antiAliasing;

    public:
        TextureLoader(const unsigned int& _bindTexture, const char* _path, bool _antiAliasing = false);
        ~TextureLoader(){};

        void ReadFile();
        unsigned int Apply();
    };
}

#endif