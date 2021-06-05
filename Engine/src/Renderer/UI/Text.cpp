#include "Renderer/UI/Text.hpp"
#include "Engine.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/Shape.hpp"
#include "Scene/Component/Transform.hpp"

#include "Debug/Log.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H


using namespace Renderer;

Text::Text(const std::string &name) : ProcessBase(name, Engine::Instance().GetResourcesManager().LoadShader(
        "./Shader/Text/Text.qsh"))
{
    _font = Engine::Instance().GetResourcesManager().LoadFont("./Asset/Fonts/Minecraft.ttf");
}

void Text::Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh)
{
    RendererPlatform::EnableDepthBuffer(false);
    RendererPlatform::SetTransparency(true);
    buffer.Bind();

    _shader.Use();
    buffer.BindTexture();
    RenderText("QuackEngine Demo:", {-0.99f, 0.925f}, 0.25f, {1.0f, 1.0f, 1.0f, 1}, screenMesh);
    RendererPlatform::BindFramebuffer(0);
}

void Text::RenderText(std::string text, Maths::Vector2f position, float scale, Maths::Vector4f color, const Mesh &quad)
{
    _shader.Use();
    float x{0};
    Maths::Vector2i size = Engine::Instance().GetWindowSize();

    _shader.SetMatrix4("projection", Maths::Matrix4::Identity());
    _shader.SetMatrix4("view", Maths::Matrix4::Translate(Maths::Vector3f(position, 0.f)));
    _shader.SetVector4f("color", color);

    // iterate through all characters
    for (auto c : text)
    {
        Character ch = _font.characters[c];

        float w = (float)ch.size.x * scale;
        float h = (float)ch.size.y * scale;

        _shader.SetMatrix4("model", Maths::Matrix4::Translate(
                {x + (w / (float) size.x), (float) ch.bearing.y / (float)size.y * scale, 0.5f}) *
                                    Maths::Matrix4::Scale({w / (float)size.x, -h / (float)size.y, 1}));

        x += ((float)(ch.advance >> 6) * scale * 2) / (float)size.x;

        ch.texture.Bind();
        quad.Draw();
    }
}