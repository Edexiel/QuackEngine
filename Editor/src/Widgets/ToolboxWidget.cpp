
#include "Widgets/ToolboxWidget.hpp"
#include "Engine.hpp"
#include "Scene/Core/World.hpp"

ToolboxWidget::ToolboxWidget()
{
    _title = "Toolbox";
}

void Save()
{
    Engine &engine = Engine::Instance();
    engine.SaveWorld(engine.GetCurrentWorld().GetName(), "./");
}
//void Load()
//{
//    Engine &engine = Engine::Instance();
//    engine.SaveWorld(engine.GetCurrentWorld().GetName(), "./");
//    World world;
//    engine.LoadWorld()
//}


void ToolboxWidget::UpdateVisible()
{

    if (ImGui::Button("Save"))
    {
        Save();
    }
//    if (ImGui::Button("Load"))
//    {
//        Load();
//    }
    ImGui::SameLine();

    if (isPlaying)
    {
        if (ImGui::Button("Stop"))
        {
            //todo
            isPlaying = !isPlaying;
        }
    }
    else
    {
        if (ImGui::Button("Play"))
        {
            Save();
            isPlaying = !isPlaying;
        }
    }


}
