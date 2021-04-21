#include "Widgets/ExplorerWidget.hpp"

#include "Scene/Core/World.hpp"
#include "Engine.hpp"

ExplorerWidget::ExplorerWidget()
{
    _title="Explorer";
}
void ExplorerWidget::UpdateVisible()
{
    if (ImGui::CollapsingHeader("Material"))
        return;

    World &world = Engine::Instance().GetCurrentWorld();

    std::vector<std::string> listMaterialName = Engine::Instance().GetResourcesManager().GetMaterialNameList();

    for (unsigned int i = 0; i < listMaterialName.size() ; i++)
    {
        if (ImGui::Selectable(listMaterialName[i].c_str(), _selected == i))
        {
            _selected = i;
            _assetName = listMaterialName[i];
            std::cout << i << std::endl;
        }
    }
}


