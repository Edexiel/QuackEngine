#include "Renderer/ProcessBase.hpp"
#include "Engine.hpp"
#include "Renderer/RendererPlatform.hpp"

using namespace Renderer;

ProcessBase::ProcessBase(const std::string &name, const Shader &shader) :
_name{name}, _shader{shader} {}

void ProcessBase::Process(const Framebuffer &buffer, const Mesh& screenMesh)
{
    buffer.Bind();

    _shader.Use();
    _shader.SetMatrix4("view", Maths::Matrix4::Identity());
    buffer.BindTexture();

    screenMesh.Draw();
    RendererPlatform::BindFramebuffer(0);
}