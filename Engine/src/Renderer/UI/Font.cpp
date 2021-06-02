#include "Renderer/UI/Font.hpp"
#include "Engine.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Framebuffer.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" /* http://nothings.org/stb/stb_image_write.h */

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h" /* http://nothings.org/stb/stb_truetype.h */

using namespace Renderer;

Font::Font(const std::string &name):ProcessBase(name, Renderer::Shader::LoadShader("./Shader/Framebuffer/BasicVertex.vs", "./Shader/Framebuffer/BasicFragment.fs"))
{}

void Font::Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh)
{
    buffer.Bind();

    _shader.Use();
    _shader.SetMatrix4("view", Maths::Matrix4::Identity());
    buffer.BindTexture();

    screenMesh.Draw();
    RendererPlatform::BindFramebuffer(0);
}