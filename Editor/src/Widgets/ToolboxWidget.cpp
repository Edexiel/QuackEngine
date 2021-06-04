
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

void ToolboxWidget::Reload()
{

    World &world = Widget::_engine.GetCurrentWorld();
    world.Clear();

    _engine.LoadWorld(world);
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
            Reload();

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


}