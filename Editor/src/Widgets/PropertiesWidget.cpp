//
// Created by g.nisi on 3/10/21.
//

#include "Widgets/PropertiesWidget.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Name.hpp"
#include "Scene/Component/Camera.hpp"
#include "Scene/Component/Light.hpp"


PropertiesWidget::PropertiesWidget()
{
    _title="Properties";
}

void PropertiesWidget::UpdateVisible()
{
    Name();
    TransformReader();
    AddComponent();
}

void PropertiesWidget::TransformReader() const
{
    Transform &transform = World::Instance().GetComponent<Transform>(_entity);


    if (ImGui::CollapsingHeader("Transform"))
        return;

    ImGui::InputFloat3("Position", transform.position.e);
    ImGui::InputFloat3("Scale", transform.scale.e);
    ImGui::InputFloat4("Rotation", transform.rotation.e);

//    for(int i = 0; i < 3; i++)
//    {
//        std::cout << e[i] << std::endl;
//    }
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
            Component::Light light;

            light.ambient = {0.1f, 0.1f, 0.1f};
            light.constant = 1.0f;
            light.linear = 0.0014f;
            light.quadratic = 0.000007f;

            light.outerSpotAngle = 10.5;
            light.spotAngle = 8.5;

            if (ImGui::MenuItem("Directional"))
            {
                light.type = Component::Light_Type::L_DIRECTIONAL;
                light.diffuse = {0,0,1};
                light.specular = {0, 0, 1};
                world.AddComponent(_entity, light);
            }
            else if (ImGui::MenuItem("Point"))
            {
                light.type = Component::Light_Type::L_POINT;
                light.diffuse = {1,1,1};
                light.specular = {1, 1, 1};

                world.AddComponent(_entity, light);
            }
            else if (ImGui::MenuItem("Spot"))
            {
                light.type = Component::Light_Type::L_SPOT;
                light.diffuse = {1,0,0};
                light.specular = {1, 0, 0};
                world.AddComponent(_entity, light);
            }
            ImGui::EndMenu();
        }


        ImGui::EndPopup();
    }

}