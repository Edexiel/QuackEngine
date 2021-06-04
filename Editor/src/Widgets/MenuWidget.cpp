#include "Widgets/MenuWidget.hpp"
#include "Scene/Core/World.hpp"
#include "Engine.hpp"
#include <fmt/core.h>

MenuWidget::MenuWidget(Editor &editor) : Widget(editor)
{
    _title = "Menu";
    _type = Type::menu;

}

void MenuWidget::UpdateVisible()
{
    bool show_scenes{false};

    if (ImGui::BeginMenu("Files"))
    {
        if (ImGui::MenuItem("Scenes"))
        {
            show_scenes = true;
        }

        ImGui::EndMenu();
    }

    if (show_scenes)
    {
        ImGui::OpenPopup("Scenes");
    }
    /** Modals **/

    //Scenes
    if (ImGui::BeginPopupModal("Scenes", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ImGui::BeginTable("Scenes", 4, ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersV))
        {
            {
                ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 100.f);
                ImGui::TableSetupColumn("Active", ImGuiTableColumnFlags_WidthFixed, 100.f);
                ImGui::TableSetupColumn("Delete", ImGuiTableColumnFlags_WidthFixed, 100.f);
                ImGui::TableSetupColumn("Save", ImGuiTableColumnFlags_WidthFixed, 70.f);
                ImGui::TableHeadersRow();
            }
            std::string CurrentWorld = _engine.GetCurrentWorld().GetName();
            int n = 0;
            for (const auto &item : _engine.GetWorldList())
            {
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", item.c_str());

                ImGui::TableSetColumnIndex(1);
                if (CurrentWorld == item)
                    ImGui::Text("Active");
                else
                {
                    if (ImGui::Button(fmt::format("SetActive##{}", n).c_str()))
                    {
                        _engine.SetCurrentWorld(item);
                    }
                }

                ImGui::TableSetColumnIndex(2);
                if (ImGui::Button(fmt::format("Delete##{}", n).c_str()))
                    _engine.RemoveWorld(item);

                ImGui::TableSetColumnIndex(3);
                if (!_engine.IsGamePlaying())
                {
                    if (ImGui::Button(fmt::format("Save##{}", n).c_str()))
                        _engine.SaveWorld(item);
                }
                else
                {
                    ImGui::Text("Playing ..");
                }
                n++;
            }
            ImGui::EndTable();
        }

//        ImGui::Text("Scene name:");
//        ImGui::SameLine();
//        static char buff[32] = "";
//        ImGui::InputText("", buff, IM_ARRAYSIZE(buff));
//
//        if (ImGui::IsItemHovered())
//        {
//            ImGui::SetTooltip("Enter new scene name without extension");
//        }
//        ImGui::SameLine();
//
//        ImGui::SetItemDefaultFocus();
//
//        if (ImGui::Button("Create", ImVec2(100, 0)))
//        {
//            std::string worldname = buff;
//            World &world = _engine.CreateWorld(worldname);
//        }
        ImGui::Separator();
        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}


void MenuWidget::Draw()
{
    if (ImGui::BeginMainMenuBar())
    {
        UpdateVisible();
        ImGui::EndMainMenuBar();
    }
}

