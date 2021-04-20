#include "Widgets/PropertiesWidget.hpp"
#include "Engine.hpp"

#include "Scene/Component/RigidBody.hpp"
#include "misc/cpp/imgui_stdlib.h"


using namespace Component;

PropertiesWidget::PropertiesWidget()
{
    _title = "Properties";
}

void PropertiesWidget::UpdateVisible()
{
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

    AddComponent();
    DeleteComponent();
}
void PropertiesWidget::NameReader() const
{
    auto &name = Engine::Instance().GetCurrentWorld().GetComponent<Name>(_entity);
    ImGui::InputText("Name", &name.name);
}
void PropertiesWidget::TransformReader() const
{
    auto &transform = Engine::Instance().GetCurrentWorld().GetComponent<Transform>(_entity);

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
    auto &light = Engine::Instance().GetCurrentWorld().GetComponent<Light>(_entity);
    if (ImGui::CollapsingHeader("Light"))
        return;

    ImGui::DragFloat3("Direction", light.direction.e);

    ImGui::ColorEdit3("Ambient", light.ambient.e);
    ImGui::ColorEdit3("Diffuse", light.diffuse.e);
    ImGui::ColorEdit3("Specular", light.specular.e);

    ImGui::DragFloat("Constant", &light.constant);
    ImGui::DragFloat("Linear", &light.linear);
    ImGui::DragFloat("Quadratic", &light.quadratic);

    ImGui::DragFloat("Spot angle", &light.spotAngle);
    ImGui::DragFloat("Outer spot angle", &light.outerSpotAngle);
}

void PropertiesWidget::CameraReader() const
{
    auto &camera = Engine::Instance().GetCurrentWorld().GetComponent<Camera>(_entity);
    if (ImGui::CollapsingHeader("Camera"))
        return;

    ImGui::Checkbox("Is perspective", &camera._isPerspective);
    float fov = (camera._fov * 180.f) / (float)M_PI;
    ImGui::DragFloat("FOV", &fov);
    camera._fov = (fov * (float)M_PI) / 180.f;

}

void PropertiesWidget::RigidBodyReader() const
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
                light.diffuse = {0, 0, 1};
                light.specular = {0, 0, 1};
                world.AddComponent(_entity, light);
            }
            else if (ImGui::MenuItem("Point"))
            {
                light.type = Component::Light_Type::L_POINT;
                light.diffuse = {1, 1, 1};
                light.specular = {1, 1, 1};

                world.AddComponent(_entity, light);
            }
            else if (ImGui::MenuItem("Spot"))
            {
                light.type = Component::Light_Type::L_SPOT;
                light.diffuse = {1, 0, 0};
                light.specular = {1, 0, 0};
                world.AddComponent(_entity, light);
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

void PropertiesWidget::DeleteComponent()
{
    World &world = Engine::Instance().GetCurrentWorld();
    if (ImGui::Button("Delete Component"))
    {
        ImGui::OpenPopup("##ComponentContextMenu_Delete");
    }
    if (ImGui::BeginPopup("##ComponentContextMenu_Delete"))
    {
        if (world.HasComponent<Camera>(_entity) && ImGui::MenuItem("Camera"))
        {
            world.RemoveComponent<Camera>(_entity);
        }
        if(world.HasComponent<Light>(_entity) && ImGui::MenuItem("Light"))
        {
            world.RemoveComponent<Light>(_entity);
        }
        if(world.HasComponent<RigidBody>(_entity) && ImGui::MenuItem("RigidBody"))
        {
            world.RemoveComponent<RigidBody>(_entity);
        }
        ImGui::EndPopup();
    }
}
