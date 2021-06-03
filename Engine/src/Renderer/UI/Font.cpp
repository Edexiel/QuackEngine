#include "Renderer/UI/Font.hpp"
#include "Engine.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Shape.hpp"

#include <cstdlib>

#include "ft2build.h"
#include FT_FREETYPE_H


using namespace Renderer;

Font::Font(const std::string &name):ProcessBase(name, Engine::Instance().GetResourcesManager().LoadShader("./Shader/Fonts/Font.qsh"))
{
    LoadFont("../../Game/Asset/Fonts/cmunrm.ttf");
}

void Font::LoadFont(const char *path)
{
    RendererPlatform::SetTransparency(true);
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, path, 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 128);
    RendererPlatform::PixelStore(1);
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
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
                {(int)face->glyph->bitmap.width, (int)face->glyph->bitmap.rows},
                {face->glyph->bitmap_left, face->glyph->bitmap_top},
                face->glyph->advance.x
        };
        _characters.insert(std::pair<char, Character>(c, character));
    }
}

void Font::Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh)
{
    RendererPlatform::EnableDepthBuffer(false);
    buffer.Bind();

    _shader.Use();
//    _shader.SetMatrix4("view", Maths::Matrix4::Scale(0.5f));
    _shader.SetMatrix4("view", Maths::Matrix4::Scale(0.5f));
    buffer.BindTexture();
    RenderText("Bien le bonjour le Denis!", 0, 0, 1, {1,1,1});
    screenMesh.Draw();
    RendererPlatform::BindFramebuffer(0);
}

void Font::RenderText(std::string text, float x, float y, float scale, Maths::Vector3f color)
{
    // activate corresponding render state
    _shader.Use();
//    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
//    glActiveTexture(GL_TEXTURE0);
//    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = _characters[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
//        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

//        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
//        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        ch.texture.Bind();
        x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
//    glBindVertexArray(0);
//    glBindTexture(GL_TEXTURE_2D, 0);
}