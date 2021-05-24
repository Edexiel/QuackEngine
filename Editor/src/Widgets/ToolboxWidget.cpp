
#include "Widgets/ToolboxWidget.hpp"
#include "Engine.hpp"
#include "Scene/Core/World.hpp"

ToolboxWidget::ToolboxWidget()
{
    _title="Toolbox";
}

void ToolboxWidget::UpdateVisible()
{
    if (ImGui::Button("Save"))
    {
        Engine &engine = Engine::Instance();
        engine.SaveWorld(engine.GetCurrentWorld().GetName(),"./");
    }

}
