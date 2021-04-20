#include "Widgets/ExplorerWidget.hpp"

#include "Scene/Core/World.hpp"

ExplorerWidget::ExplorerWidget()
{
    _title="Explorer";
}
void ExplorerWidget::UpdateVisible()
{
    if (ImGui::CollapsingHeader("Material"))
        return;

    World &world = World::Instance();

    std::vector<std::string> listMaterialName = world.GetResourcesManager().GetMaterialNameList();

    for (unsigned int i = 0; i < listMaterialName.size() ; i++)
    {
        if (ImGui::Selectable(listMaterialName[i].c_str(), _selected == i))
        {
            _selected = i;
            std::cout << i << std::endl;
        }
    }
}


