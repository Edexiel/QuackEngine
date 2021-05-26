
#include "Widgets/ToolboxWidget.hpp"
#include "Engine.hpp"
#include "Scene/Core/World.hpp"

ToolboxWidget::ToolboxWidget():_engine{Engine::Instance()}
{
    _title = "Toolbox";
}

void ToolboxWidget::Save()
{
    _engine.SaveWorld(_engine.GetCurrentWorld().GetName());
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
            //todo : clear world and restore
            isPlaying = !isPlaying;
            _engine.SetGamePlaying(isPlaying);

        }
    }
    else
    {
        if (ImGui::Button("Play"))
        {
            Save();
            isPlaying = !isPlaying;
            _engine.SetGamePlaying(isPlaying);
        }
    }


}
