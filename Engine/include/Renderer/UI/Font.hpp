#ifndef QUACKENGINE_FONT_HPP
#define QUACKENGINE_FONT_HPP

#include "Resources/Asset.hpp"

#include "Maths/Vector2.hpp"
#include "Renderer/Texture.hpp"

#include <unordered_map>
namespace Renderer
{
    struct Character
    {
        Renderer::Texture texture;  // ID handle of the glyph texture
        Maths::Vector2i size;       // Size of glyph
        Maths::Vector2i bearing;    // Offset from baseline to left/top of glyph
        int advance;    // Offset to advance to next glyph
    };

    struct Font : public Resources::Asset
    {
        Font();
        Font(const char* path);
        std::unordered_map<char, Character> characters;
        static Font LoadFont(const char *path);
    };
}

#endif //QUACKENGINE_FONT_HPP
