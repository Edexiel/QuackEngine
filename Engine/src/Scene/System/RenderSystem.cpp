#include "Scene/System/RenderSystem.hpp"

#include "Scene/Component/Transform.hpp"
#include "Scene/Component/Model.hpp"

#include "Scene/Core/World.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Scene/Component/Camera.hpp"
#include "Renderer/Shape.hpp"

using namespace Renderer;

RenderSystem::RenderSystem()
{
    _quadMesh = Shape::CreateQuad();
    _shader = World::Instance().GetResourcesManager().LoadShader(
            "../../Engine/Shader/Framebuffer/BasicVertex.vs",
            "../../Engine/Shader/Framebuffer/BasicFragment.fs");
}

void RenderSystem::Draw( Component::Camera& camera)
{
    camera.GetFramebuffer().Bind();

    RendererPlatform::ClearColor({0.0f, 0.0f, 0.0f, 1.f});
    RendererPlatform::Clear();

    /*for (Entity entity: _entities)
    {
        auto &t = World::Instance().GetComponent<Transform>(entity);
        auto &m = World::Instance().GetComponent<Component::Model>(entity);

        m.Draw(camera.GetProjection(), camera.GetView(), t.GetMatrix());
    }*/

    DrawMaterials();
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

void RenderSystem::AddMaterial(Renderer::MaterialInterface materialInterface)
{
    _listMaterial.push_back(materialInterface);
}

void RenderSystem::RemoveMaterial(Renderer::MaterialInterface materialInterface)
{
    for (unsigned int i = 0; i < _listMaterial.size(); i++)
    {
        if (materialInterface.get() == _listMaterial[i].get())
        {
            _listMaterial.erase(_listMaterial.cbegin() + i);
        }
    }
}

void RenderSystem::AddMesh(Renderer::MaterialInterface materialInterface, Renderer::Mesh mesh, Entity entity)
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

void RenderSystem::DrawMaterials()
{
    World &world = World::Instance();

    for (auto material : _mapMaterial)
    {
        material.first->Apply();

        for (unsigned int i = 0; i < material.second.size(); i++)
        {
            material.first->shader.SetMatrix4("model", world.GetComponent<Transform>(material.second[i].second).GetMatrix());
            material.second[i].first.Draw(world.GetComponent<Component::Model>(material.second[i].second).GetVertexType());
            //material.second[i].first.Draw(VertexType::V_NORMALMAP);

        }
    }
}
