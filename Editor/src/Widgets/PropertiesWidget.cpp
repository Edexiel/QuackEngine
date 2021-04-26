#include "Widgets/PropertiesWidget.hpp"
#include "Engine.hpp"

#include "Scene/Component/RigidBody.hpp"
#include "misc/cpp/imgui_stdlib.h"

#include <algorithm>


using namespace Component;

PropertiesWidget::PropertiesWidget()
{
    _title = "Properties";
}

void PropertiesWidget::UpdateVisible()
{
    if (_propertiesSwitch == PROPERTIES_SHOW_ASSET)
        return;

    //NameReader();
    World &world = Engine::Instance().GetCurrentWorld();
    if(world.HasComponent<Name>(_entity))
        NameReader();
    if(world.HasComponent<Transform>(_entity))
        TransformReader();
    if(world.HasComponent<Light>(_entity))
        LightReader();
    if(world.HasComponent<Camera>(_entity))
        CameraReader();
    if(world.HasComponent<RigidBody>(_entity))
        RigidBodyReader();
    if (world.HasComponent<Model>(_entity))
        ModelReader();

    AddComponent();
    DeleteComponent();
}
void PropertiesWidget::NameReader()
{
    auto &name = Engine::Instance().GetCurrentWorld().GetComponent<Name>(_entity);
    ImGui::InputText("Name", &name.name);
}
void PropertiesWidget::TransformReader()
{
    auto &transform = Engine::Instance().GetCurrentWorld().GetComponent<Transform>(_entity);

    if (ImGui::CollapsingHeader("Transform"))
        return;

    ImGui::DragFloat3("Position", transform.position.e);
    ImGui::DragFloat3("Scale", transform.scale.e);


    Maths::Vector3f v = transform.rotation.ToEuler() * (180.f / (float)M_PI);
    ImGui::DragFloat3("Rotation", v.e);
    v = v * (M_PI / 180.f);
    transform.rotation = Maths::Quaternion::EulerToQuaternion(v);

}

void PropertiesWidget::LightReader()
{
    Component::Light &light = Engine::Instance().GetCurrentWorld().GetComponent<Component::Light>(_entity);

    if (ImGui::CollapsingHeader("Light"))
        return;

    std::vector<std::string> listLightType;
    listLightType.emplace_back("Point");
    listLightType.emplace_back("Directional");
    listLightType.emplace_back("Spot");

    if (ImGui::BeginCombo("Light Type", listLightType[(int) light.type].c_str()))
    {
        for (int n = 0; n < listLightType.size(); n++)
        {
            bool isSelected = (listLightType[(int)light.type] ==
                                listLightType[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(listLightType[n].c_str(), isSelected))
            {
                switch (n)
                {
                    case 0:
                        light.type = Component::Light_Type::L_POINT;
                        break;
                    case 1:
                        light.type = Component::Light_Type::L_DIRECTIONAL;
                        break;
                    case 2:
                        light.type = Component::Light_Type::L_SPOT;
                        break;

                }
                Engine::Instance().GetRendererInterface().lightSystem->Update(true);
            }
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (ImGui::ColorEdit3("Ambient", light.ambient.e) ||
        ImGui::ColorEdit3("Diffuse", light.diffuse.e) ||
        ImGui::ColorEdit3("Specular", light.specular.e))
    {
        Engine::Instance().GetRendererInterface().lightSystem->Update(true);
    }
    if (light.type != Component::Light_Type::L_DIRECTIONAL)
    {
        if (ImGui::InputFloat("Linear Attenuation", &light.linear, 0.0f, 0.0f, "%.9f") ||
            ImGui::InputFloat("Quadratic Attenuation", &light.quadratic, 0.0f, 0.0f, "%.9f"))
        {
            Engine::Instance().GetRendererInterface().lightSystem->Update(true);
        }
    }
    if (light.type == Component::Light_Type::L_SPOT)
    {
        if (ImGui::DragFloat("Spot Angle", &light.spotAngle) ||
           ImGui::DragFloat("Outer Spot Angle", &light.outerSpotAngle))
        {
            Engine::Instance().GetRendererInterface().lightSystem->Update(true);
        }
    }

}

void PropertiesWidget::ModelReader()
{
    if (ImGui::CollapsingHeader("Model"))
        return;

    Component::Model& model = Engine::Instance().GetCurrentWorld().GetComponent<Component::Model>(_entity);

    std::vector<std::string> listModel = Engine::Instance().GetResourcesManager().GetModelNameList();

    if  (ImGui::BeginCombo("##combo1", model.name.c_str()))
    {
        for (int n = 0; n < listModel.size(); n++)
        {
            bool isSelected = (model.name == listModel[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(listModel[n].c_str(), isSelected))
            {
                model.name = listModel[n];
                model = Engine::Instance().GetResourcesManager().LoadModel(listModel[n].c_str(), Renderer::VertexType::V_NORMALMAP);
                Engine::Instance().GetRendererInterface().renderSystem->SetMaterials();
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    for (unsigned int i = 0; i < model.GetNumberMesh() ; i++)
    {
        ImGui::SliderInt((std::string("Material Mesh ") + std::to_string(i + 1)).c_str(), (int*)model.GetMeshMaterialIndex(i), 0, (int)model.GetNumberMaterial() - 1);
        Engine::Instance().GetRendererInterface().renderSystem->SetMaterials();
    }

    std::vector<std::string> listMaterial = Engine::Instance().GetResourcesManager().GetMaterialNameList();

    for (unsigned int i = 0; i < model.GetNumberMaterial() ; i++)
    {
        if  (ImGui::BeginCombo((std::string ("##comboMaterial") + std::to_string(i)).c_str(), model.GetMaterial(i)->name.c_str()))
        {
            for (int n = 0; n < listMaterial.size(); n++)
            {
                bool is_selected = (model.name == listMaterial[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(listMaterial[n].c_str(), is_selected))
                {
                    Renderer::MaterialInterface materialInterface = Engine::Instance().GetResourcesManager().LoadMaterial(listMaterial[n].c_str());
                    model.ChangeMaterial(materialInterface, i);
                    Engine::Instance().GetRendererInterface().renderSystem->SetMaterials();
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
    }
    if (ImGui::Button("Add Material"))
    {
        model.AddMaterial(Engine::Instance().GetResourcesManager().LoadMaterial(DEFAULT_MATERIAL_STRING));
    }
    if (ImGui::Button("Remove Material"))
    {
        model.RemoveMaterial(model.GetNumberMaterial() - 1);
    }
}

void PropertiesWidget::CameraReader()
{
    auto &camera = Engine::Instance().GetCurrentWorld().GetComponent<Camera>(_entity);
    if (ImGui::CollapsingHeader("Camera"))
        return;

    ImGui::Checkbox("Is perspective", &camera._isPerspective);
    float fov = (camera._fov * 180.f) / (float)M_PI;
    ImGui::DragFloat("FOV", &fov);
    camera._fov = (fov * (float)M_PI) / 180.f;

}

void PropertiesWidget::RigidBodyReader()
{
    if (ImGui::CollapsingHeader("RigidBody"))
        return;
}

void PropertiesWidget::AddComponent()
{
    World &world = Engine::Instance().GetCurrentWorld();
    if (ImGui::Button("Add Component"))
    {
        ImGui::OpenPopup("##ComponentContextMenu_Add");
    }

    if (ImGui::BeginPopup("##ComponentContextMenu_Add"))
    {
        //Camera
        if (ImGui::MenuItem("Camera"))
        {
            world.AddComponent(_entity, Component::Camera(1280, 720, 1000, -1, 20 * 3.1415 / 180));
        }

        //Light
        if (ImGui::BeginMenu("Light"))
        {
            AddLight();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Model"))
        {
            std::vector<std::string> listModel = Engine::Instance().GetResourcesManager().GetModelNameList();
            for (int n = 0; n < listModel.size(); n++)
            {
                if (ImGui::MenuItem(listModel[n].c_str()))
                {
                    world.AddComponent(_entity, Engine::Instance().GetResourcesManager().LoadModel(listModel[n].c_str(), Renderer::VertexType::V_NORMALMAP));
                }
            }
            ImGui::EndMenu();
        }

        if (ImGui::MenuItem("RigidBody"))
        {
            world.AddComponent(_entity, RigidBody());
        }
        ImGui::EndPopup();
    }

}

void PropertiesWidget::AddLight()
{
    World &world = Engine::Instance().GetCurrentWorld();

    Component::Light light;

    light.ambient = {0.1f, 0.1f, 0.1f};
    light.diffuse = {0.7f,0.7f,0.7f};
    light.specular = {1.0, 1.0f, 1.0f};
    light.constant = 1.0f;
    light.linear = 0.0014f;
    light.quadratic = 0.000007f;

    light.outerSpotAngle = 10.5;
    light.spotAngle = 8.5;

    if (ImGui::MenuItem("Directional"))
    {
        light.type = Component::Light_Type::L_DIRECTIONAL;
        world.AddComponent(_entity, light);
    }
    else if (ImGui::MenuItem("Point"))
    {
        light.type = Component::Light_Type::L_POINT;
        world.AddComponent(_entity, light);
    }
    else if (ImGui::MenuItem("Spot"))
    {
        light.type = Component::Light_Type::L_SPOT;
        world.AddComponent(_entity, light);
    }

        if (ImGui::MenuItem("RigidBody"))
        {
            world.AddComponent(_entity, RigidBody());
        }
        ImGui::EndPopup();
    }

void PropertiesWidget::DeleteComponent()
{

}
