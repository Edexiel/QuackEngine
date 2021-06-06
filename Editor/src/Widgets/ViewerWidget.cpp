#include <Scene/Component/Name.hpp>
#include "Widgets/ViewerWidget.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/EngineComponents.hpp"
#include "Editor.hpp"

using namespace Component;

ViewerWidget::ViewerWidget(Editor &editor) : Widget(editor)
{
    _title = "Viewer";
}

void ViewerWidget::UpdateVisible()
{
    World &world = _engine.GetCurrentWorld();

    for (Entity entity : world.GetEntityManager()->GetEntities())
    {
        std::string name = fmt::format("{}({})", world.GetComponent<Name>(entity).name, entity);
        if (ImGui::Selectable(name.c_str(), _editor.selectedEntity == (std::int32_t) entity))
        {
            _editor.showProperties = true;
            _editor.selectedEntity = (std::int32_t) entity;
        }
    }
    AddEntity();
    ImGui::SameLine();
    DestroyEntity();
    ImGui::SameLine();
    DuplicateEntity();
}

void ViewerWidget::AddEntity()
{
    if (ImGui::Button("Add"))
    {
        World &world = _engine.GetCurrentWorld();
        _editor.selectedEntity = (std::int32_t) world.CreateEntity("GameObject");
        Transform t;
        world.AddComponent(_editor.selectedEntity, t);
    }
}

void ViewerWidget::DestroyEntity()
{
    if (ImGui::Button("Destroy") && _editor.selectedEntity > -1)
    {
        _engine.GetCurrentWorld().DestroyEntity(_editor.selectedEntity);
        _editor.selectedEntity = -1;
        _editor.showProperties = false;
    }
}

void ViewerWidget::DuplicateEntity()
{
    if (ImGui::Button("Duplicate") && _editor.selectedEntity > -1)
    {
        World& world = _engine.GetCurrentWorld();
        std::int32_t entity = _editor.selectedEntity;
        Entity newEntity =  world.CreateEntity(world.GetComponent<Name>(entity).name);
        if (world.HasComponent<Name>(entity))
            world.AddComponent(newEntity, world.GetComponent<Name>(entity));
        if (world.HasComponent<Transform>(entity))
            world.AddComponent(newEntity, world.GetComponent<Transform>(entity));
        if (world.HasComponent<Light>(entity))
            world.AddComponent(newEntity, world.GetComponent<Light>(entity));
        if (world.HasComponent<Camera>(entity))
            world.AddComponent(newEntity, world.GetComponent<Camera>(entity));
        if (world.HasComponent<RigidBody>(entity) && world.HasComponent<Transform>(entity))
            world.AddComponent(newEntity, world.GetComponent<RigidBody>(entity));
        if (world.HasComponent<Model>(entity))
            world.AddComponent(newEntity, world.GetComponent<Model>(entity));
        if (world.HasComponent<Animator>(entity))
            world.AddComponent(newEntity, world.GetComponent<Animator>(entity));
        if (world.HasComponent<CharacterController>(entity))
            world.AddComponent(newEntity, world.GetComponent<CharacterController>(entity));
        if (world.HasComponent<CameraGameplay>(entity))
            world.AddComponent(newEntity, world.GetComponent<CameraGameplay>(entity));
        if (world.HasComponent<ParticleEmitter>(entity))
            world.AddComponent(newEntity, world.GetComponent<ParticleEmitter>(entity));
        if (world.HasComponent<SimpleShadow>(entity))
            world.AddComponent(newEntity, world.GetComponent<SimpleShadow>(entity));
    }
}
