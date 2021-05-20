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
            "../../Engine/Shader/Framebuffer/BasicVertex.vs",
            "../../Engine/Shader/Framebuffer/BasicFragment.fs");
}

void PostProcessManager::ApplyPostProcess(const Framebuffer& framebuffer)
{
    for (unsigned int i = 0; i < _listProcess.size(); i++)
    {
        _listProcess[i]->Process(framebuffer, _quadMesh);
    }
}
