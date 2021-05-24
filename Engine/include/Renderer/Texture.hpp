#ifndef QUACKENGINE_TEXTURE_HPP
#define QUACKENGINE_TEXTURE_HPP

#include <string>
#include <filesystem>
#include "Resources/Asset.hpp"

namespace Renderer
{
    class Texture : public Resources::Asset
    {
    private:
    unsigned int _id{0};

    public:
        Texture();
        Texture(unsigned int id);
        ~Texture()=default;
        unsigned int GetID() const;
        static Texture LoadTexture(const std::filesystem::path& path);
        void Bind(unsigned int index = 0) const;
    };
}

#endif // QUACKENGINE_TEXTURE_HPP
