#include "Renderer/UI/Font.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Debug/Log.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

using namespace Renderer;

Font::Font() : Resources::Asset(Resources::AssetType::A_FONT)
{}

Font Font::LoadFont(const std::filesystem::path & path)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        Log_Error("ERROR::FREETYPE: Could not init FreeType Library");
        return Font();
    }

    FT_Face face;
    if (FT_New_Face(ft, path.string().c_str(), 0, &face))
    {
        Log_Error("ERROR::FREETYPE: Failed to load font");
        return Font();
    }

    FT_Set_Pixel_Sizes(face, 0, 128);
    RendererPlatform::PixelStore(1);
    Font font;
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            Log_Error("ERROR::FREETYTPE: Failed to load Glyph");
            continue;
        }
        // generate texture
        Renderer::Texture texture = RendererPlatform::CreateTexture();
        RendererPlatform::SetTextureImage2D(
                face->glyph->bitmap.buffer,
                1,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows
        );
        // set texture options
        RendererPlatform::TextureParameter();

        // now store character for later use
        Character character = {
                texture,
                {(int) face->glyph->bitmap.width, (int) face->glyph->bitmap.rows},
                {face->glyph->bitmap_left, face->glyph->bitmap_top},
                face->glyph->advance.x
        };
        font.characters.insert(std::pair<char, Character>(c, character));
    }
    return font;
}