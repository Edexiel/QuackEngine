#include "Scene/System/RenderSystem.hpp"

#include "Engine.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Scene/Component/Animator.hpp"
#include "Scene/Core/World.hpp"

#include "Scene/Component/Camera.hpp"
#include "Scene/Component/Transform.hpp"

using namespace Renderer;
using namespace Component;


void RenderSystem::Draw(Component::Camera &camera)
{
    Renderer::RendererPlatform::SetTransparency(true);
    Renderer::RendererPlatform::EnableDepthBuffer(true);
    RendererPlatform::Clear();

    camera.GetFramebuffer().Bind();
    RendererPlatform::Clear();
    DrawMaterials(camera.GetProjection(), camera.GetView());
    RendererPlatform::BindFramebuffer(0);
}

void RenderSystem::Draw(const Maths::Matrix4 &projection, const Maths::Matrix4 &view)
{
    RendererPlatform::SetTransparency(true);
    RendererPlatform::EnableDepthBuffer(true);
    RendererPlatform::Clear();

    DrawMaterials(projection, view);
}

void RenderSystem::AddMesh(const Renderer::MaterialInterface &materialInterface, const Renderer::Mesh &mesh, Entity entity)
{
    auto it = _mapMaterial.find(materialInterface);

    if (it == _mapMaterial.end())
    {
        _mapMaterial.insert({materialInterface, std::vector<std::pair<Renderer::Mesh, Entity>>()});
        it = _mapMaterial.find(materialInterface);
    }

    it->second.emplace_back(mesh, entity);
}

void RenderSystem::SetMaterials()
{
    _mapMaterial.erase(_mapMaterial.cbegin(), _mapMaterial.cend());
    MaterialInterface material;
    World &world = Engine::Instance().GetCurrentWorld();
    for (Entity entity: _entities)
    {
        auto &t = world.GetComponent<Transform>(entity);
        auto &m = world.GetComponent<Model>(entity).model;

        for (unsigned int i = 0; i < m.GetNumberMesh(); i++)
        {
            material = m.GetMaterial(m.GetMesh(i).materialIndex);
            AddMesh(material, m.GetMesh(i), entity);
        }
    }
}

void RenderSystem::DrawMaterials(const Maths::Matrix4 &projection, const Maths::Matrix4 &view)
{
    if (_lastLinkEntitiesNumbers != _entities.size() || _lastLinkEntitiesNumbers == 0)
    {
        _lastLinkEntitiesNumbers = _entities.size();
        SetMaterials();
    }

    Engine &engine = Engine::Instance();

    for (auto it : _mapMaterial)
    {
        it.first->Apply();
        it.first->shader.SetMatrix4("projection", projection);
        it.first->shader.SetMatrix4("view", view);

        for (unsigned int i = 0; i < it.second.size(); i++)
        {
            it.first->shader.SetMatrix4("model", engine.GetCurrentWorld().GetComponent<Transform>(
                    it.second[i].second).GetMatrix());

            if (it.second[i].first.GetType() == Renderer::VertexType::V_SKELETAL)
            {
                if (it.first->hasSkeleton &&
                    engine.GetCurrentWorld().HasComponent<Animator>(it.second[i].second))
                {
                    engine.GetCurrentWorld().GetComponent<Animator>(it.second[i].second).Update(
                            engine.GetTimeManager().GetDeltaTime());
                    engine.GetCurrentWorld().GetComponent<Animator>(it.second[i].second).SetShader(it.first->shader);
                }
            }
            it.second[i].first.Draw();
        }
    }
}

void RenderSystem::UpdateModel(const Renderer::ModelRenderer &newModel)
{
    World &world = Engine::Instance().GetCurrentWorld();
    for (Entity entity: _entities)
    {
        auto &m = world.GetComponent<Model>(entity).model;

        if (m.name == newModel.name)
        {
            Renderer::ModelRenderer::ReLoadModel(m, newModel);
        }
    }
}
