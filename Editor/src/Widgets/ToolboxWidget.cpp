
#include "Widgets/ToolboxWidget.hpp"
#include "Engine.hpp"
#include "Scene/Core/World.hpp"

ToolboxWidget::ToolboxWidget(Editor &editor) : Widget(editor)
{
    _title = "Toolbox";
}

void ToolboxWidget::Save()
{
    _engine.SaveWorld(_engine.GetCurrentWorld().GetName());
}



void ToolboxWidget::UpdateVisible()
{

    if (!_engine.IsGamePlaying())
    {
        if (ImGui::Button("Save"))
        {
            Save();
        }
    }

    ImGui::SameLine();

    if (isPlaying)
    {
        if (ImGui::Button("Stop"))
        {
            isPlaying = !isPlaying;
            World &world = _engine.GetCurrentWorld();
            world.Clear();

            world.Register();
            _engine.LoadWorld(world);
            _engine.SetCurrentWorld(world.GetName());
            _engine.SetGamePlaying(isPlaying);


        }
        ImGui::SameLine();
        ImGui::Text("FPS: %i", (unsigned int) _engine.GetFps());
    }
    else
    {
        if (ImGui::Button("Play"))
        {
            Save();
            isPlaying = !isPlaying;
            _engine.SetGamePlaying(isPlaying);
            _engine.GetCurrentWorld().InitGame();
        }
    }
    ImGui::SameLine();
    ImGui::Text("Entities: %zu",_engine.GetCurrentWorld().GetEntityManager()->GetEntities().size());



}