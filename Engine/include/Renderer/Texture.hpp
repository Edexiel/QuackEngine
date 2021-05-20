#ifndef QUACKENGINE_TEXTURE_HPP
#define QUACKENGINE_TEXTURE_HPP

#include <string>
#include "Resources/Asset.hpp"

namespace Renderer
{
    class Texture : public Resources::Asset
    {
    private:
    unsigned int _ID{0};

    public:
        Texture();
        Texture(unsigned int ID);
        ~Texture();
        unsigned int GetID() const;
        static Texture LoadTexture(const char* filepath);
        void Bind(unsigned int index = 0);
    };
}

#endif // QUACKENGINE_TEXTURE_HPP
