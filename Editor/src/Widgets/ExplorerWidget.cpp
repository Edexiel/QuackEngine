#include "Widgets/ExplorerWidget.hpp"

#include "Scene/Core/World.hpp"
#include "Engine.hpp"

ExplorerWidget::ExplorerWidget()
{
    _title="Explorer";
}
void ExplorerWidget::UpdateVisible()
{
    Engine &engine = Engine::Instance();

    std::vector<std::string> listName = engine.GetResourcesManager().GetMaterialNameList();

    unsigned int offset = 0;

    if (!ImGui::CollapsingHeader("Material"))
    {
        offset += DisplayList(listName, offset);
        if (!_newMaterial && ImGui::Button("Add Material"))
        {
            _newMaterial = true;
        }
        else if (_newMaterial)
        {
            ImGui::InputText("New Material Name", _newMaterialTextBuffer, 32);
            if (_newMaterial && ImGui::Button("Create"))
            {
                engine.GetResourcesManager().GenerateMaterial(_newMaterialTextBuffer, Renderer::Material());
                _newMaterial = false;
            }
        }
    }
    listName = engine.GetResourcesManager().GetTextureNameList();

    if (!ImGui::CollapsingHeader("Texture"))
        offset += DisplayList(listName, offset);

    listName = engine.GetResourcesManager().GetModelNameList();

    if (!ImGui::CollapsingHeader("Model"))
        offset += DisplayList(listName, offset);
}

unsigned int ExplorerWidget::DisplayList(std::vector<std::string> &listName, unsigned int offset)
{
    for (unsigned int i = 0; i < listName.size() ; i++)
    {
        if (ImGui::Selectable(listName[i].c_str(), _selected == i + offset))
        {
            _propertiesSwitch = PROPERTIES_SHOW_ASSET;
            _selected = i + offset;
            _assetName = listName[i];
            std::cout << _selected << std::endl;
        }
    }
    return listName.size();
}