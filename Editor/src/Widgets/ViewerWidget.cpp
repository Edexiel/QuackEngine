#include "Widgets/ViewerWidget.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"
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
    DestroyEntity();
}

void ViewerWidget::AddEntity()
{
    if (ImGui::Button("Add entity"))
    {
        World &world = _engine.GetCurrentWorld();
        _editor.selectedEntity = (std::int32_t) world.CreateEntity("GameObject");
        Transform t;
        world.AddComponent(_editor.selectedEntity, t);
    }
}

void ViewerWidget::DestroyEntity()
{
    if (ImGui::Button("Destroy entity") && _editor.selectedEntity > -1)
    {
        _engine.GetCurrentWorld().DestroyEntity(_editor.selectedEntity);
        _editor.selectedEntity = -1;
        _editor.showProperties = false;
    }
}
