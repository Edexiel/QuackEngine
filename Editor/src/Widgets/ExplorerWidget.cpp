#include "Widgets/ExplorerWidget.hpp"

#include "Scene/Core/World.hpp"
#include "Engine.hpp"
#include "Editor.hpp"

ExplorerWidget::ExplorerWidget(Editor &editor) : Widget(editor)
{
    _title = "Explorer";
}

void ExplorerWidget::UpdateVisible()
{

    std::vector<std::string> listName = _engine.GetResourcesManager().GetMaterialNameList();

    unsigned int offset = 0;

    if (!ImGui::CollapsingHeader("Material"))
    {
        offset += DisplayList(listName, offset);
        AddMaterial(offset);
        ImGui::SameLine();
        RemoveMaterial(listName);

    }
    listName = _engine.GetResourcesManager().GetTextureNameList();

    if (!ImGui::CollapsingHeader("Texture"))
        offset += DisplayList(listName, offset);

    listName = _engine.GetResourcesManager().GetModelNameList();

    if (!ImGui::CollapsingHeader("Model"))
        offset += DisplayList(listName, offset);

    listName = _engine.GetResourcesManager().GetAnimationNameList();
    if (!ImGui::CollapsingHeader("Animation"))
        offset += DisplayList(listName, offset);
}

unsigned int ExplorerWidget::DisplayList(std::vector<std::string> &listName, unsigned int offset)
{
    for (unsigned int i = 0; i < listName.size(); i++)
    {
        if (ImGui::Selectable(listName[i].c_str(), _selected == i + offset))
        {
            _editor.showProperties = false;
            _selected = i + offset;
            _editor.assetName = listName.at(i);
        }
    }
    return listName.size();
}

void ExplorerWidget::AddMaterial(unsigned int& offset)
{
    if (!_newMaterial && ImGui::Button("Add Material"))
    {
        _newMaterial = true;
    }
    else if (_newMaterial)
    {
        ImGui::InputText("New Material Name", _newMaterialTextBuffer, 32);
        if (ImGui::Button("Create"))
        {
            _engine.GetResourcesManager().GenerateMaterial(_newMaterialTextBuffer, Renderer::Material());
            _newMaterial = false;
        }
    }
}

void ExplorerWidget::RemoveMaterial(const std::vector<std::string>& listMaterialName)
{
    if (ImGui::Button("Remove Material"))
        if (_selected < listMaterialName.size())
        {
            _engine.GetResourcesManager().DestroyMaterial(listMaterialName[_selected]);
            _selected = 0;
        }

}
