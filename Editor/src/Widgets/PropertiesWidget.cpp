//
// Created by g.nisi on 3/10/21.
//

#include "Widgets/PropertiesWidget.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Name.hpp"
#include "Scene/Component/Camera.hpp"
#include "Scene/Component/Light.hpp"
#include "Scene/Component/Model.hpp"


PropertiesWidget::PropertiesWidget()
{
    _title="Properties";
}

void PropertiesWidget::UpdateVisible()
{
    World& world = World::Instance();

    TransformReader();
    if (world.HasComponent<Component::Light>(_entity))
        LightReader();
    if (world.HasComponent<Component::Model>(_entity))
        ModelReader();


    AddComponent();
}

void PropertiesWidget::TransformReader() const
{
    Transform &transform = World::Instance().GetComponent<Transform>(_entity);

    if (ImGui::CollapsingHeader("Transform"))
        return;

    ImGui::DragFloat3("Position", transform.position.e);
    ImGui::DragFloat3("Scale", transform.scale.e);
    Maths::Vector3f v = transform.rotation.ToEuler();
    ImGui::DragFloat3("Rotation", v.e);
    v = v * (M_PI / 180.f);
    transform.rotation = Maths::Quaternion::EulerToQuaternion(v);

}

void PropertiesWidget::LightReader() const
{
    Component::Light &light = World::Instance().GetComponent<Component::Light>(_entity);

    if (ImGui::CollapsingHeader("Light"))
        return;

    std::vector<std::string> listLightType;
    listLightType.emplace_back("Point");
    listLightType.emplace_back("Directional");
    listLightType.emplace_back("Spot");

    if (ImGui::BeginCombo("##combo1", listLightType[(int) light.type].c_str()))
    {
        for (int n = 0; n < listLightType.size(); n++)
        {
            bool is_selected = (listLightType[(int) light.type].c_str() ==
                                listLightType[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(listLightType[n].c_str(), is_selected))
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
                World::Instance().GetRendererInterface().lightSystem->Update(true);
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (ImGui::SliderFloat3("Ambient", light.ambient.e, 0, 1) ||
        ImGui::SliderFloat3("Diffuse", light.diffuse.e, 0, 1) ||
        ImGui::SliderFloat3("Specular", light.specular.e, 0, 1))
    {
        World::Instance().GetRendererInterface().lightSystem->Update(true);
    }
    if (light.type != Component::Light_Type::L_DIRECTIONAL)
    {
        if (ImGui::InputFloat("Linear Attenuation", &light.linear, 0.0f, 0.0f, "%.9f") ||
            ImGui::InputFloat("Quadratic Attenuation", &light.quadratic, 0.0f, 0.0f, "%.9f"))
        {
            World::Instance().GetRendererInterface().lightSystem->Update(true);
        }
    }
    if (light.type == Component::Light_Type::L_SPOT)
    {
        if (ImGui::DragFloat("Spot Angle", &light.spotAngle) ||
           ImGui::DragFloat("Outer Spot Angle", &light.outerSpotAngle))
        {
            World::Instance().GetRendererInterface().lightSystem->Update(true);
        }
    }

}

void PropertiesWidget::ModelReader() const
{
    if (ImGui::CollapsingHeader("Model"))
        return;

    Component::Model& model = World::Instance().GetComponent<Component::Model>(_entity);

    std::vector<std::string> listModel = World::Instance().GetResourcesManager().GetModelNameList();

    if  (ImGui::BeginCombo("##combo1", model.name.c_str()))
    {
        for (int n = 0; n < listModel.size(); n++)
        {
            bool is_selected = (model.name == listModel[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(listModel[n].c_str(), is_selected))
            {
                model.name = listModel[n];
                model = World::Instance().GetResourcesManager().LoadModel(listModel[n].c_str(), Renderer::VertexType::V_NORMALMAP);
                World::Instance().GetRendererInterface().renderSystem->SetMaterials();
            }

            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    for (unsigned int i = 0; i < model.GetNumberMesh() ; i++)
    {
        ImGui::SliderInt((std::string("Material Mesh ") + std::to_string(i + 1)).c_str(), (int*)model.GetMeshMaterialIndex(i), 0, (int)model.GetNumberMaterial() - 1);
        World::Instance().GetRendererInterface().renderSystem->SetMaterials();
    }

    std::vector<std::string> listMaterial = World::Instance().GetResourcesManager().GetMaterialNameList();

    for (unsigned int i = 0; i < model.GetNumberMaterial() ; i++)
    {
        if  (ImGui::BeginCombo((std::string ("##comboMaterial") + std::to_string(i)).c_str(), model.GetMaterial(i)->name.c_str()))
        {
            for (int n = 0; n < listMaterial.size(); n++)
            {
                bool is_selected = (model.name == listMaterial[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(listMaterial[n].c_str(), is_selected))
                {
                    Renderer::MaterialInterface materialInterface = World::Instance().GetResourcesManager().LoadMaterial(listMaterial[n].c_str());
                    model.ChangeMaterial(materialInterface, i);
                    World::Instance().GetRendererInterface().renderSystem->SetMaterials();
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
    }
    if (ImGui::Button("Add Material"))
    {
        model.AddMaterial(World::Instance().GetResourcesManager().LoadMaterial(DEFAULT_MATERIAL_STRING));
    }
    if (ImGui::Button("Remove Material"))
    {
        model.RemoveMaterial(model.GetNumberMaterial() - 1);
    }
}

void PropertiesWidget::AddComponent()
{
    World &world = World::Instance();
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
            std::vector<std::string> listModel = World::Instance().GetResourcesManager().GetModelNameList();
            for (int n = 0; n < listModel.size(); n++)
            {
                if (ImGui::MenuItem(listModel[n].c_str()))
                {
                    world.AddComponent(_entity, World::Instance().GetResourcesManager().LoadModel(listModel[n].c_str(), Renderer::VertexType::V_NORMALMAP));
                }
            }
            ImGui::EndMenu();
        }

        ImGui::EndPopup();
    }

}

void PropertiesWidget::AddLight()
{
    World &world = World::Instance();

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


}