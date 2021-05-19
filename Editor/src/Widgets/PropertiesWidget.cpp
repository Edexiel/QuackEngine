#include "Widgets/PropertiesWidget.hpp"
#include "Engine.hpp"

#include "Scene/Component/RigidBody.hpp"
#include "Scene/System/PhysicsSystem.hpp"
#include "misc/cpp/imgui_stdlib.h"
#include "Maths/Common.hpp"

#include "Scene/Component/Animator.hpp"

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
    if (world.HasComponent<Name>(_entity))
        NameReader();
    if (world.HasComponent<Transform>(_entity))
        TransformReader();
    if (world.HasComponent<Light>(_entity))
        LightReader();
    if (world.HasComponent<Camera>(_entity))
        CameraReader();
    if (world.HasComponent<RigidBody>(_entity))
        RigidBodyReader();
    if (world.HasComponent<Model>(_entity))
        ModelReader();
    if (world.HasComponent<Animator>(_entity))
        AnimatorReader();

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

    ImGuiIO &io = ImGui::GetIO();
    auto &transform = Engine::Instance().GetCurrentWorld().GetComponent<Transform>(_entity);

    if (ImGui::CollapsingHeader("Transform"))
        return;

    ImGui::DragFloat3("Position", transform.position.e);
    ImGui::DragFloat3("Scale", transform.scale.e);
    bool isRotationChange = ImGui::DragFloat3("Rotation", _eulerRot.e);

    if (!ImGui::IsMouseDragging(0) && !isRotationChange)
        _eulerRot = transform.rotation.ToEuler() * RadToDeg<float>();
    if(isRotationChange)
        transform.rotation = Maths::Quaternion::EulerToQuaternion(_eulerRot * DegToRad<float>());
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
            bool isSelected = (listLightType[(int) light.type] ==
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

    Component::Model &model = Engine::Instance().GetCurrentWorld().GetComponent<Component::Model>(_entity);

    std::vector<std::string> listModel = Engine::Instance().GetResourcesManager().GetModelNameList();

    if  (ImGui::BeginCombo("##ModelCombo", model.name.c_str()))
    {
        for (int n = 0; n < listModel.size(); n++)
        {
            bool isSelected = (model.name ==
                               listModel[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(listModel[n].c_str(), isSelected))
            {
                model.name = listModel[n];
                model = Engine::Instance().GetResourcesManager().LoadModel(listModel[n].c_str(),
                                                                           Renderer::VertexType::V_NORMALMAP);
                Engine::Instance().GetRendererInterface().renderSystem->SetMaterials();
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    for (unsigned int i = 0; i < model.GetNumberMesh(); i++)
    {
        ImGui::SliderInt((std::string("Material Mesh ") + std::to_string(i + 1)).c_str(),
                         (int *) model.GetMeshMaterialIndex(i), 0, (int) model.GetNumberMaterial() - 1);
        Engine::Instance().GetRendererInterface().renderSystem->SetMaterials();
    }

    std::vector<std::string> listMaterial = Engine::Instance().GetResourcesManager().GetMaterialNameList();

    for (unsigned int i = 0; i < model.GetNumberMaterial(); i++)
    {
        if (ImGui::BeginCombo((std::string("##comboMaterial") + std::to_string(i)).c_str(),
                              model.GetMaterial(i)->name.c_str()))
        {
            for (int n = 0; n < listMaterial.size(); n++)
            {
                bool is_selected = (model.name ==
                                    listMaterial[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(listMaterial[n].c_str(), is_selected))
                {
                    Renderer::MaterialInterface materialInterface = Engine::Instance().GetResourcesManager().LoadMaterial(
                            listMaterial[n].c_str());
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

void PropertiesWidget::AnimatorReader()
{
    if (ImGui::CollapsingHeader("Animator"))
        return;

    Component::Animator& animator = Engine::Instance().GetCurrentWorld().GetComponent<Component::Animator>(_entity);

    std::vector<std::string> listAnimation = Engine::Instance().GetResourcesManager().GetAnimationNameList();

    if  (ImGui::BeginCombo("##AnimatorCombo", animator.GetAnimation().name.c_str()))
    {
        for (int n = 0; n < listAnimation.size(); n++)
        {
            bool isSelected = (animator.GetAnimation().name == listAnimation[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(listAnimation[n].c_str(), isSelected))
            {
                animator.SetAnimation(*(Renderer::Animation*)(Engine::Instance().GetResourcesManager().GetAsset(listAnimation[n].c_str())));
                Engine::Instance().GetRendererInterface().renderSystem->SetMaterials();
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
}


void PropertiesWidget::CameraReader()
{
    auto &camera = Engine::Instance().GetCurrentWorld().GetComponent<Camera>(_entity);
    if (ImGui::CollapsingHeader("Camera"))
        return;

    ImGui::Checkbox("Is perspective", &camera._isPerspective);
    float fov = camera._fov * RadToDeg<float>();
    ImGui::DragFloat("FOV", &fov, 1.f, 0.f, 180.f);

    camera._fov = fov * DegToRad<float>();

}

void PropertiesWidget::RigidBodyReader()
{
    if (ImGui::CollapsingHeader("RigidBody"))
        return;

    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(_entity);

    RigidBodyChangeBodyType(rigidBody);
    RigidBodyResizeShape(rigidBody);
    RigidBodySetIsTrigger(rigidBody);
    RigidBodySetIsGravityEnabled(rigidBody);
    RigidBodySetMass(rigidBody);

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
                    world.AddComponent(_entity, Engine::Instance().GetResourcesManager().LoadModel(listModel[n].c_str(),
                                                                                                   Renderer::VertexType::V_NORMALMAP));
                }
            }
            ImGui::EndMenu();
        }

        AddRigidBody();


        ImGui::EndPopup();
    }

}

void PropertiesWidget::AddLight()
{
    World &world = Engine::Instance().GetCurrentWorld();

    Component::Light light;

    light.ambient = {0.1f, 0.1f, 0.1f};
    light.diffuse = {0.7f, 0.7f, 0.7f};
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

        //Light
        if (world.HasComponent<Light>(_entity) && ImGui::MenuItem("Light"))
        {
            world.RemoveComponent<Light>(_entity);
        }

        if (world.HasComponent<Model>(_entity) && ImGui::MenuItem("Model"))
        {
            world.RemoveComponent<Model>(_entity);
        }
        if (world.HasComponent<RigidBody>(_entity) && ImGui::MenuItem("Rigidbody"))
        {
            auto physicsWorld = world.GetPhysicsWorld();
            physicsWorld->destroyRigidBody(world.GetComponent<RigidBody>(_entity).rb);
            world.RemoveComponent<RigidBody>(_entity);
        }
        ImGui::EndPopup();
    }
}

void PropertiesWidget::AddRigidBody()
{
    if (ImGui::BeginMenu("RigidBody"))
    {
        World &world = Engine::Instance().GetCurrentWorld();
        if (ImGui::MenuItem("Box collider"))
        {
            world.AddComponent(_entity, RigidBody());
            PhysicsSystem::SetRigidBody(_entity);
            PhysicsSystem::SetType(_entity, BodyType::STATIC);
            PhysicsSystem::AddBoxCollider(_entity, {1.0f, 1.0f, 1.0f});
        }
        if (ImGui::MenuItem("Sphere collider"))
        {
            world.AddComponent(_entity, RigidBody());
            PhysicsSystem::SetRigidBody(_entity);
            PhysicsSystem::SetType(_entity, BodyType::STATIC);
            PhysicsSystem::AddSphereCollider(_entity, 1.f);

        }
        if(ImGui::MenuItem("Capsule collider"))
        {
            world.AddComponent(_entity, RigidBody());
            PhysicsSystem::SetRigidBody(_entity);
            PhysicsSystem::SetType(_entity, BodyType::STATIC);
            PhysicsSystem::AddCapsuleCollider(_entity, 1.f, 1.0f);
        }
        ImGui::EndMenu();
    }
}

void PropertiesWidget::RigidBodyChangeBodyType(Component::RigidBody& rigidBody)
{
    const char *enumBodyType[]{"Static", "Kinematic", "Dynamic"};
    int bodyType = (int) rigidBody.GetBodyType();
    if(ImGui::Combo("BodyType",&bodyType, enumBodyType, IM_ARRAYSIZE(enumBodyType)))
    {
        switch (bodyType)
        {
            case 0:
            {
                if (rigidBody.GetBodyType() != BodyType::STATIC)
                    PhysicsSystem::SetType(_entity, BodyType::STATIC);

                break;
            }
            case 1:
            {
                if (rigidBody.GetBodyType() != BodyType::KINEMATIC)
                    PhysicsSystem::SetType(_entity, BodyType::KINEMATIC);

                break;
            }
            case 2:
            {
                if (rigidBody.GetBodyType() != BodyType::DYNAMIC)
                    PhysicsSystem::SetType(_entity, BodyType::DYNAMIC);

                break;
            }
            default:
                break;
        }
    }
}

void PropertiesWidget::RigidBodyResizeShape(Component::RigidBody& rigidBody)
{
    if(rigidBody.GetCollisionShapeType() == CollisionShapeType::CONVEX_POLYHEDRON)
    {
        Maths::Vector3<float> halfExtend = rigidBody.GetHalfExtends();
        if(ImGui::DragFloat3("Half extend", halfExtend.e))
        {
            PhysicsSystem::ResizeBoxCollider(_entity, halfExtend);
        }
    }
    if(rigidBody.GetCollisionShapeType() == CollisionShapeType::SPHERE)
    {
        float radius = rigidBody.GetRadius();
        ImGui::DragFloat("Radius", &radius, 0.1f, 0.001f, FLT_MAX);
        PhysicsSystem::ResizeSphereCollider(_entity, radius);
    }
    if(rigidBody.GetCollisionShapeType() == CollisionShapeType::CAPSULE)
    {
        float radius = rigidBody.GetRadius();
        float height = rigidBody.GetHeight();

        ImGui::DragFloat("Radius", &radius, 0.1f, 0.001f, FLT_MAX);
        ImGui::DragFloat("height", &height, 0.1f, 0.001f, FLT_MAX);

        PhysicsSystem::ResizeCapsuleCollider(_entity, radius, height);
    }
}

void PropertiesWidget::RigidBodySetIsTrigger(Component::RigidBody& rigidBody)
{
    bool isTrigger = rigidBody.GetIsTrigger();
    if(ImGui::Checkbox("Trigger", &isTrigger))
        PhysicsSystem::SetIsTrigger(_entity, isTrigger);

}

void PropertiesWidget::RigidBodySetMass(RigidBody &rigidBody)
{
    float mass = rigidBody.GetMass();
    if(ImGui::DragFloat("mass", &mass))
    {
        PhysicsSystem::SetMass(_entity, mass);

        //todo: change this code if the dev of reactphysics3d fix this bug.
        if(rigidBody.GetBodyType() == BodyType::STATIC)
        {
            PhysicsSystem::SetType(_entity, BodyType::DYNAMIC);// Sorcellerie Obligatoire due a reactphysics3d
            PhysicsSystem::SetType(_entity, BodyType::STATIC);// Sorcellerie Obligatoire due a reactphysics3d
        }
        else if (rigidBody.GetBodyType() == BodyType::KINEMATIC)
        {
            PhysicsSystem::SetType(_entity, BodyType::DYNAMIC);// Sorcellerie Obligatoire due a reactphysics3d
            PhysicsSystem::SetType(_entity, BodyType::KINEMATIC);// Sorcellerie Obligatoire due a reactphysics3d
        }
    }
}

void PropertiesWidget::RigidBodySetIsGravityEnabled(RigidBody &rigidBody)
{
    bool isGravityEnabled = rigidBody.GetIsGravityEnabled();
    if(ImGui::Checkbox("Gravity Enabled", &isGravityEnabled))
        PhysicsSystem::SetIsGravityEnable(_entity, isGravityEnabled);
}
