#include "Renderer/UI/Font.hpp"
#include "Engine.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Shape.hpp"

#include <cstdlib>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" /* http://nothings.org/stb/stb_image_write.h */

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h" /* http://nothings.org/stb/stb_truetype.h */

using namespace Renderer;

Font::Font(const std::string &name):ProcessBase(name, Engine::Instance().GetResourcesManager().LoadShader("./Shader/Fonts/Font.qsh"))
{
//    LoadFont("../../Game/Asset/Fonts/cmunrm.ttf");
}

void Font::LoadFont(const char *path)
{
    /* load font file */
    long size;
    unsigned char* fontBuffer;

    FILE* fontFile = fopen(path, "rb");
    fseek(fontFile, 0, SEEK_END);
    size = ftell(fontFile); /* how long is the file ? */
    fseek(fontFile, 0, SEEK_SET); /* reset */

    fontBuffer = (unsigned char*)malloc(size);

    fread(fontBuffer, size, 1, fontFile);
    fclose(fontFile);

    /* prepare font */
    stbtt_fontinfo info;
    if (!stbtt_InitFont(&info, fontBuffer, 0))
    {
        printf("failed\n");
    }

    /* create a bitmap for the phrase */
    int l_h = 50;

    /* calculate font scaling */
    float scale = stbtt_ScaleForPixelHeight(&info, (float)l_h);

    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);

    ascent = roundf(ascent * scale);
    descent = roundf(descent * scale);

    for (unsigned char c = 0; c < 128; c++)
    {
        Character character;
        character.size = {256, 256};

        stbtt_GetCodepointHMetrics(&info, c, &character.advance, &character.bearing.x);//how wide is this character

        int c_x1, c_y1, c_x2, c_y2;
        /* get bounding box for character (may be offset to account for chars that dip above or below the line */
        stbtt_GetCodepointBitmapBox(&info, c, scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

        /* compute y (different characters have different heights */
        int y = ascent + c_y1;
        int x = roundf(character.advance * scale);

        /* render character (stride and offset is important here) */
//        int byteOffset = roundf(character.bearing.x * scale) + (y * character.size.x);

        auto* tempBitmap = (unsigned char*)calloc(character.size.x * character.size.y, sizeof(unsigned char));
        stbtt_MakeCodepointBitmap(&info, tempBitmap, c_x2 - c_x1, c_y2 - c_y1, character.size.x, scale, scale, c);

        Renderer::Texture texture = RendererPlatform::CreateTexture();
        RendererPlatform::TextureParameter();
        RendererPlatform::EnableBlend(true);
        RendererPlatform::SetTextureImage2D(tempBitmap, 1, character.size.x, character.size.y);

//        _characters[c] = character;
        _characters.insert(std::pair<char, Character>(c, character));
//        texture.Bind();
        free(tempBitmap);
    }
    free(fontBuffer);
//    free(bitmapReverse);
}

void Font::Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh)
{
    RendererPlatform::EnableDepthBuffer(false);
    buffer.Bind();

    _shader.Use();
//    _shader.SetMatrix4("view", Maths::Matrix4::Scale(0.5f));
    _shader.SetMatrix4("view", Maths::Matrix4::Scale(1.0f));
//    buffer.BindTexture();
//    TestFont();
//    _characters['a'].texture.Bind();
    screenMesh.Draw();
    RendererPlatform::BindFramebuffer(0);
}

void Font::TestFont()
{
    /* load font file */
    long size;
    unsigned char* fontBuffer;

    FILE* fontFile = fopen("../../Game/Asset/Fonts/cmunrm.ttf", "rb");
    fseek(fontFile, 0, SEEK_END);
    size = ftell(fontFile); /* how long is the file ? */
    fseek(fontFile, 0, SEEK_SET); /* reset */

    fontBuffer = (unsigned char*)malloc(size);

    fread(fontBuffer, size, 1, fontFile);
    fclose(fontFile);

    /* prepare font */
    stbtt_fontinfo info;
    if (!stbtt_InitFont(&info, fontBuffer, 0))
    {
        printf("failed\n");
    }

    int b_w = 1920; /* bitmap width */
    int b_h = 1080; /* bitmap height */
    int l_h = 540; /* line height */

    /* create a bitmap for the phrase */
    auto* bitmap = (unsigned char*)calloc(b_w * b_h, sizeof(unsigned char));

    /* calculate font scaling */
    float scale = stbtt_ScaleForPixelHeight(&info, (float)l_h);

    char* word = "A";

    int x = 0;

    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);

    ascent = roundf(ascent * scale);
    descent = roundf(descent * scale);

    int i;
    for (i = 0; i < strlen(word); ++i)
    {
        /* how wide is this character */
        int ax;
        int lsb;
        stbtt_GetCodepointHMetrics(&info, word[i], &ax, &lsb);

        /* get bounding box for character (may be offset to account for chars that dip above or below the line */
        int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&info, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

        /* compute y (different characters have different heights */
        int y = ascent + c_y1;

        /* render character (stride and offset is important here) */
        int byteOffset = x + roundf(lsb * scale) + (y * b_w);
        stbtt_MakeCodepointBitmap(&info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

        /* advance x */
        x += roundf(ax * scale);

        /* add kerning */
        int kern;
        kern = stbtt_GetCodepointKernAdvance(&info, word[i], word[i + 1]);
        x += roundf(kern * scale);
    }

    auto* bitmapReverse = (unsigned char*)calloc(b_w * b_h, sizeof(unsigned char));
    for(int i = 0; i < b_h; i++)
        for(int j = 0; j < b_w; j++)
            bitmapReverse[j + i * b_w] = bitmap[j + (b_h - i) * b_w];

    Renderer::Texture texture = RendererPlatform::CreateTexture();
    RendererPlatform::TextureParameter();
    RendererPlatform::EnableBlend(true);
    RendererPlatform::SetTextureImage2D(bitmapReverse, 1, b_w, b_h);
    texture.Bind();
//    _shader.SetSampler("ourTexture");

    free(fontBuffer);
    free(bitmap);
    free(bitmapReverse);
}

