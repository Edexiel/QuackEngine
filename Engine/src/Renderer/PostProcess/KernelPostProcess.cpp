#include "Renderer/PostProcess/KernelPostProcess.hpp"

#include "Engine.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Framebuffer.hpp"

Renderer::KernelPostProcess::KernelPostProcess(const std::string& name) :
ProcessBase(name, Engine::Instance().GetResourcesManager().LoadShader("./Shader/PostProcess/KernelPostProcess.qsh"))
{}

void Renderer::KernelPostProcess::Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh)
{
    buffer.Bind();

    _shader.Use();
    _shader.SetMatrix4("view", Maths::Matrix4::Identity());

    for (unsigned int i = 0; i < 9; i++)
    {
        _shader.SetFloat((std::string("kernel[") + std::to_string(i) + "]").c_str(), array[i]);
    }
    _shader.SetFloat("offset", offset);

    buffer.BindTexture();

    screenMesh.Draw();
    RendererPlatform::BindFramebuffer(0);
}
