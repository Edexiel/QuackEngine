#include "Scene/System/RenderSystem.hpp"

#include "Engine.hpp"
#include "Renderer/RendererPlatform.hpp"
#include "Scene/Core/World.hpp"

#include "Scene/Component/Animator.hpp"
#include "Scene/Component/Model.hpp"
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

void RenderSystem::AddMesh(const Renderer::MaterialInterface &materialInterface, const Renderer::Mesh &mesh, Maths::Vector3f offset, Entity entity)
{
    auto it = _mapMaterial.find(materialInterface);

    if (it == _mapMaterial.end())
    {
        _mapMaterial.insert({materialInterface, std::vector<MaterialMeshData>()});
        it = _mapMaterial.find(materialInterface);
    }

    it->second.push_back({mesh, offset, entity});
}

void RenderSystem::SetMaterials()
{
    _mapMaterial.erase(_mapMaterial.cbegin(), _mapMaterial.cend());
    MaterialInterface material;
    World &world = Engine::Instance().GetCurrentWorld();

    for (Entity entity: _entities)
    {
        auto &t = world.GetComponent<Transform>(entity);
        auto &m = world.GetComponent<Model>(entity);

        for (unsigned int i = 0; i < m.model.GetNumberMesh(); i++)
        {
            material = m.model.GetMaterial(m.model.GetMesh(i).materialIndex);
            AddMesh(material, m.model.GetMesh(i),m.offset, entity);
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
            it.first->shader.SetMatrix4("model", Maths::Matrix4::Translate(it.second[i].offset)
                    * engine.GetCurrentWorld().GetComponent<Transform>(
                    it.second[i].entity).GetMatrix());

            if (it.second[i].mesh.GetType() == Renderer::VertexType::V_SKELETAL)
            {
                if (it.first->hasSkeleton &&
                    engine.GetCurrentWorld().HasComponent<Animator>(it.second[i].entity))
                {
                    engine.GetCurrentWorld().GetComponent<Animator>(it.second[i].entity).SetShader(it.first->shader);
                }
            }
            it.second[i].mesh.Draw();
        }
    }
}

void RenderSystem::Clear()
{
    for (auto it : _mapMaterial)
    {
        it.second.clear();
    }

    _mapMaterial.clear();
    _mapMaterial.rehash(0);
    _lastLinkEntitiesNumbers = 0;
}

void RenderSystem::UpdateModel(const Renderer::ModelRenderer &newModel)
{
    World &world = Engine::Instance().GetCurrentWorld();
    for (Entity entity: _entities)
    {
        auto &m = world.GetComponent<Model>(entity).model;

        if (m.GetPath() == newModel.GetPath())
        {
            Renderer::ModelRenderer::ReLoadModel(m, newModel);
        }
    }
}