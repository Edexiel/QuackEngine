#include <Widgets/AssetWidget.hpp>
#include "Scene/Core/World.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Engine.hpp"

AssetWidget::AssetWidget() :
_camera{Component::Camera(1280,720,1000, -1, 20 * 3.1415 / 180)}
{
    _title = "Properties";

    _camera.SetView(Maths::Matrix4::Identity());
}

void AssetWidget::UpdateVisible()
{
    if (_propertiesSwitch == PROPERTIES_SHOW_ENTITY)
        return;


    Engine& engine = Engine::Instance();

    ImGui::BeginChild("ViewportRender");
    //ImVec2 wsize = ImGui::GetWindowSize();

    ImGui::Text("%s", _assetName.c_str());

    std::string type = Resources::ResourcesManager::GetFileType(_assetName);

    if (type == NO_TYPE_STRING)
        return ImGui::EndChild();
    else if (type == "fbx")
        DisplayModel();
    else if (type == "ogg" || type == "mp3" || type == "wav")
        DisplaySound();
    else if (type == "png" || type == "jpg" || type == "epg")
        DisplayTexture();
    else
        DisplayMaterial();

    ImGui::EndChild();

}

void AssetWidget::DisplayMaterial()
{
    Engine& engine = Engine::Instance();
    Renderer::MaterialInterface material = engine.GetResourcesManager().LoadMaterial(_assetName.c_str());

    ImGui::ColorEdit3("Ambient", material->ambient.e);
    ImGui::ColorEdit3("Diffuse", material->diffuse.e);
    ImGui::ColorEdit3("Specular", material->specular.e);
    ImGui::SliderFloat("Shininess", &(material->shininess), 1, 512, "%.1f");

    std::vector<std::string> listTexture = Engine::Instance().GetResourcesManager().GetTextureNameList();
    listTexture.insert(listTexture.cbegin(), EMPTY_TEXTURE_STRING);

    std::string name = engine.GetResourcesManager().GetName(material->colorTexture);
    if (SelectTexture(material->colorTexture, listTexture, name.c_str(), "Color Texture"))
    {
        material->GenerateShader();
        engine.GetRendererInterface().lightSystem->Update(true);
    }

    name = engine.GetResourcesManager().GetName(material->diffuseTexture);
    if (SelectTexture(material->diffuseTexture, listTexture, name.c_str(), "Diffuse Texture"))
    {
        material->GenerateShader();
        engine.GetRendererInterface().lightSystem->Update(true);
    }

    name = engine.GetResourcesManager().GetName(material->specularTexture);
    if (SelectTexture(material->specularTexture, listTexture, name.c_str(), "Specular Texture"))
    {
        material->GenerateShader();
        engine.GetRendererInterface().lightSystem->Update(true);
    }

    name = engine.GetResourcesManager().GetName(material->normalMap);
    if (SelectTexture(material->normalMap, listTexture, name.c_str(), "Normal Texture"))
    {
        material->GenerateShader();
        engine.GetRendererInterface().lightSystem->Update(true);
    }
}

std::string AssetWidget::SelectInList(const std::vector<std::string>& list, const char* currentlySelected, const char* comboName)
{
    std::string selected = currentlySelected;

    if  (ImGui::BeginCombo(comboName, currentlySelected))
    {
        for (int n = 0; n < list.size(); n++)
        {
            bool isSelected = (currentlySelected == list[n]);
            if (ImGui::Selectable(list[n].c_str(), isSelected))
            {
                selected = list[n];
                break;
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    return selected;

}

bool AssetWidget::SelectTexture(Renderer::Texture& texture, const std::vector<std::string>& list, const char* currentTexture, const char* comboName)
{
    std::string selectedTexture = SelectInList(list, currentTexture, comboName);

    if (selectedTexture != currentTexture)
    {
        if (selectedTexture == EMPTY_TEXTURE_STRING)
            texture = Renderer::Texture();
        else
            texture = Engine::Instance().GetResourcesManager().LoadTexture(selectedTexture.c_str());
        return true;
    }
    return false;
}

void AssetWidget::DisplayTexture()
{
    Renderer::Texture texture = Engine::Instance().GetResourcesManager().LoadTexture(_assetName.c_str());
    ImVec2 wsize = ImGui::GetWindowSize();
    if (wsize.x < wsize.y)
        ImGui::Image((ImTextureID)(size_t)texture.GetID(), {wsize.x, wsize.x}, ImVec2(0, 1), ImVec2(1, 0));
    else
        ImGui::Image((ImTextureID)(size_t)texture.GetID(), {wsize.y, wsize.y}, ImVec2(0, 1), ImVec2(1, 0));

}

void AssetWidget::DisplayModel()
{
    Component::Model model = Engine::Instance().GetResourcesManager().LoadModel(_assetName.c_str());

    std::vector<std::string> listModelType;
    listModelType.emplace_back("CLASSIC");
    listModelType.emplace_back("NORMAL_MAP");
    listModelType.emplace_back("SKELETAL");

    std::string selected = SelectInList(listModelType, listModelType[(int)model.GetVertexType()].c_str(), "Model Vertex Type");

    if (selected != listModelType[(int)model.GetVertexType()])
    {
        if (selected == "CLASSIC")
            Engine::Instance().GetResourcesManager().ReLoadModel(_assetName.c_str(), Renderer::VertexType::V_CLASSIC);
        else if (selected == "NORMAL_MAP")
            Engine::Instance().GetResourcesManager().ReLoadModel(_assetName.c_str(), Renderer::VertexType::V_NORMALMAP);
        else if (selected == "SKELETAL")
            Engine::Instance().GetResourcesManager().ReLoadModel(_assetName.c_str(), Renderer::VertexType::V_SKELETAL);
    }

}

void AssetWidget::DisplaySound()
{
    Engine::Instance().GetResourcesManager().LoadSound(_assetName.c_str(), Audio::SoundType::S_MASTER);
}