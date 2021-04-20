#include "Scene/System/RenderSystem.hpp"

#include "Scene/Core/World.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Renderer/Shape.hpp"

#include "Debug/Log.hpp"

using namespace Renderer;

RenderSystem::RenderSystem()
{
    _quadMesh = Shape::CreateQuad();
    _shader = World::Instance().GetResourcesManager().LoadShader(
            "../../Engine/Shader/Framebuffer/BasicVertex.vs",
            "../../Engine/Shader/Framebuffer/BasicFragment.fs");
}

void RenderSystem::Draw(Component::Camera& camera)
{
    camera.GetFramebuffer().Bind();

    RendererPlatform::ClearColor({0.0f, 0.0f, 0.0f, 1.f});
    RendererPlatform::Clear();

    DrawMaterials(camera);

    RendererPlatform::BindFramebuffer(0);
}

void RenderSystem::DrawTextureInFramebuffer(unsigned int framebufferIndex, unsigned int textureIndex)
{
    RendererPlatform::BindFramebuffer(framebufferIndex);

    RendererPlatform::ClearColor({0.2f, 0.2f, 0.2f, 1.f});
    RendererPlatform::Clear();

    _shader.Use();
    _shader.SetMatrix4("view", Maths::Matrix4::Identity());
    RendererPlatform::BindTexture(textureIndex, 0);

    _quadMesh.Draw();
}

void RenderSystem::AddMesh(Renderer::MaterialInterface materialInterface, const Renderer::Mesh& mesh, Entity entity)
{
    auto it = _mapMaterial.find(materialInterface);

    if (it == _mapMaterial.end())
    {
        _mapMaterial.insert({materialInterface, std::vector<std::pair<Renderer::Mesh, Entity>>()});
        it = _mapMaterial.find(materialInterface);
    }

    it->second.push_back({mesh, entity});
}

void RenderSystem::SetMaterials()
{

    _mapMaterial.erase(_mapMaterial.cbegin(), _mapMaterial.cend());
    MaterialInterface material;

    for (Entity entity: _entities)
    {
        auto &t = World::Instance().GetComponent<Transform>(entity);
        auto &m = World::Instance().GetComponent<Component::Model>(entity);

        for (unsigned int i = 0; i < m.GetNumberMesh(); i++)
        {
            material = m.GetMaterial(m.GetMesh(i).materialIndex);
            AddMesh(material, m.GetMesh(i), entity);
        }
    }
}

void RenderSystem::DrawMaterials(Component::Camera& camera)
{
    if (_lastLinkEntitiesNumbers != _entities.size() || _lastLinkEntitiesNumbers == 0)
    {
        _lastLinkEntitiesNumbers = _entities.size();
        SetMaterials();
    }

    World &world = World::Instance();

    for (auto material : _mapMaterial)
    {
        material.first->Apply();
        material.first->shader.SetMatrix4("projection", camera.GetProjection());
        material.first->shader.SetMatrix4("view", camera.GetView());

        for (unsigned int i = 0; i < material.second.size(); i++)
        {
            material.first->shader.SetMatrix4("model", world.GetComponent<Transform>(material.second[i].second).GetMatrix());
            material.second[i].first.Draw();

        }
    }
}
