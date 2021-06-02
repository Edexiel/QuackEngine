#include "Renderer/PostProcessManager.hpp"

#include "Engine.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Mesh.hpp"
#include "Renderer/Shape.hpp"

using namespace Renderer;

void PostProcessManager::DrawTextureInFramebuffer(unsigned int framebufferIndex, unsigned int textureIndex)
{
    RendererPlatform::BindFramebuffer(framebufferIndex);

    RendererPlatform::ClearColor({0.2f, 0.2f, 0.2f, 1.f});
    RendererPlatform::Clear();

    _shader.Use();
    _shader.SetMatrix4("view", Maths::Matrix4::Identity());
    RendererPlatform::BindTexture(textureIndex, 0);

    _quadMesh.Draw();
}

void PostProcessManager::Init()
{
    _quadMesh = Shape::CreateQuad();
    _shader = Shader::LoadShader(
            "./Shader/Framebuffer/BasicVertex.vs",
            "./Shader/Framebuffer/BasicFragment.fs");
}

void PostProcessManager::ApplyPostProcess(const Framebuffer& framebuffer)
{
    for (auto & _listProces : _listProcess)
    {
        _listProces->Process(framebuffer, _quadMesh);
    }
}

void PostProcessManager::AddProcess(ProcessBase *process)
{
    _listProcess.emplace_back(process);
}

void PostProcessManager::AddProcess(std::unique_ptr<ProcessBase> &process)
{
    _listProcess.emplace_back(std::move(process));
}
