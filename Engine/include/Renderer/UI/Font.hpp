#ifndef QUACKENGINE_FONT_HPP
#define QUACKENGINE_FONT_HPP

#include "Renderer/ProcessBase.hpp"
#include "Maths/Vector2.hpp"
#include "Renderer/Texture.hpp"
namespace Renderer
{
    struct Character
    {
        Renderer::Texture texture;  // ID handle of the glyph texture
        Maths::Vector2i size;       // Size of glyph
        Maths::Vector2i bearing;    // Offset from baseline to left/top of glyph
        int advance;    // Offset to advance to next glyph
    };

    class Font : public ProcessBase
    {
    private:
        void TestFont();
        std::unordered_map<char, Character> _characters;
        void LoadFont(const char * path);
    public:
        Font() = default;
        Font(const std::string &name);
        void Process(const Framebuffer &buffer, const Mesh &screenMesh) final;
    };
}
#endif //QUACKENGINE_FONT_HPP
