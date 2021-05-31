#include "Widgets/MenuWidget.hpp"

MenuWidget::MenuWidget(Editor &editor) : Widget(editor)
{
    _title = "Menu";
    _type = Type::menu;

}

void MenuWidget::UpdateVisible()
{
    bool new_scene{false};
    if (ImGui::BeginMenu("Files"))
    {
        if (ImGui::MenuItem("New scene..."))
        {
            new_scene = true;
        }

        if (ImGui::MenuItem("Load scene"))
        {
//            for (const auto &item : _assetName)
//            {
//
//            }
        }

        ImGui::Separator();
        if (ImGui::MenuItem("Import object"))
        {}
        ImGui::EndMenu();
    }

    if (new_scene)
    {
        ImGui::OpenPopup("New scene");
    }

    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("Undo", "CTRL+Z"))
        {
            if (ImGui::BeginPopup("my_select_popup"))
            {
                ImGui::Text("Aquarium");
                ImGui::Separator();
                ImGui::EndPopup();
            }

        }
        if (ImGui::MenuItem("Redo", "CTRL+Y"))
        {
        } // Disabled item
        ImGui::Separator();
        if (ImGui::MenuItem("Cut", "CTRL+X"))
        {
        }
        if (ImGui::MenuItem("Copy", "CTRL+C"))
        {
        }
        if (ImGui::MenuItem("Paste", "CTRL+V"))
        {
        }
        ImGui::EndMenu();
    }

    if (ImGui::BeginPopupModal("New scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
        ImGui::Separator();

        if (ImGui::Button("OK", ImVec2(120, 0)))
        { ImGui::CloseCurrentPopup(); }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
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

