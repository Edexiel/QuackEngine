#include "Widgets/ViewerWidget.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"
#include "Engine.hpp"

using namespace Component;

ViewerWidget::ViewerWidget()
{
    _title = "Viewer";
}

void ViewerWidget::UpdateVisible()
{
    World &world = Engine::Instance().GetCurrentWorld();

    int n = 0;
    for (Entity entity : world.GetEntityManager()->GetEntities())
    {
        char buf[32];
        sprintf(buf, (world.GetComponent<Name>(entity).name + "(%d)").c_str(), n);
        if (ImGui::Selectable(buf, _selected == n))
        {
            _selected = n;
            _entity = entity;
            std::cout << _entity << std::endl;
        }
        n++;
    }
    AddEntity();
    DestroyEntity();
}

void ViewerWidget::AddEntity()
{
    if (ImGui::Button("Add entity"))
    {
        World &world = Engine::Instance().GetCurrentWorld();
        _entity = world.CreateEntity("GameObject");
        _selected = _entity;
        Transform t;
        world.AddComponent(_entity, t);
    }
}

void ViewerWidget::DestroyEntity() const
{
    if (ImGui::Button("Destroy entity") && _selected > -1)
    {
        Engine::Instance().GetCurrentWorld().DestroyEntity(_entity);
    }
}
