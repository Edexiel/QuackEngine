#include "Widgets/PropertiesWidget.hpp"
#include "Engine.hpp"

#include "Scene/Component/EngineComponents.hpp"
#include "Scene/System/EngineSystems.hpp"

#include "Player/PlayerComponent.hpp"

#include "Renderer/ModelRenderer.hpp"

#include "misc/cpp/imgui_stdlib.h"

#include <algorithm>
#include "Editor.hpp"


using namespace Component;

PropertiesWidget::PropertiesWidget(Editor &editor) : Widget(editor)
{
    _title = "Properties";
}

void PropertiesWidget::UpdateVisible()
{
    if (_editor.showProperties)
    {
        ShowComponents();
        return;
    }
    ShowAssets();

}

void PropertiesWidget::ShowComponents()
{

    //NameReader();
    World &world = _engine.GetCurrentWorld();
    std::int32_t entity = _editor.selectedEntity;
    if (world.HasComponent<Name>(entity))
        NameReader();
    if (world.HasComponent<Transform>(entity))
        TransformReader();
    if (world.HasComponent<Light>(entity))
        LightReader();
    if (world.HasComponent<Camera>(entity))
        CameraReader();
    if (world.HasComponent<RigidBody>(entity) && world.HasComponent<Transform>(entity))
        RigidBodyReader();
    if (world.HasComponent<Model>(entity))
        ModelReader();
    if (world.HasComponent<Animator>(entity))
        AnimatorReader();
    if (world.HasComponent<CharacterController>(entity))
        CharacterControllerReader();
    if (world.HasComponent<CameraGameplay>(entity))
        CameraGameplayReader();
    if (world.HasComponent<ParticleEmitter>(entity))
        ParticleReader();
    if (world.HasComponent<SimpleShadow>(entity))
        SimpleShadowReader();

    AddComponent();
    ImGui::SameLine();
    DeleteComponent();
}


void PropertiesWidget::ShowAssets()
{

    ImGui::BeginChild("ViewportRender");

    ImGui::Text("%s", _editor.assetName.c_str());

    std::string type = Resources::ResourcesManager::GetFileType(_editor.assetName);

    const Resources::Asset *asset = _engine.GetResourcesManager().GetAsset(_editor.assetName);

    if (asset)
    {
        if (asset->GetType() == Resources::AssetType::A_MODEL)
            DisplayModel(asset);
        else if (asset->GetType() == Resources::AssetType::A_SOUND)
            DisplaySound(asset);
        else if (asset->GetType() == Resources::AssetType::A_TEXTURE)
            DisplayTexture(asset);
        else if (asset->GetType() == Resources::AssetType::A_MATERIAL)
            DisplayMaterial(asset);
    }

    ImGui::EndChild();

}

void PropertiesWidget::DisplayMaterial(const Resources::Asset *asset)
{
    auto *material = (Renderer::Material *) asset;

    if (ImGui::Checkbox("Check Lights", &material->checkLight))
    {
        material->GenerateShader();
        _engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();
    }
    if (ImGui::Checkbox("Has Skeleton", &material->hasSkeleton))
    {
        material->GenerateShader();
        _engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();
    }

    ImGui::ColorEdit4("Color", material->color.e);

    if (material->checkLight)
    {
        ImGui::ColorEdit3("Ambient", material->ambient.e);
        ImGui::ColorEdit3("Diffuse", material->diffuse.e);
        ImGui::ColorEdit3("Specular", material->specular.e);
        ImGui::SliderFloat("Shininess", &(material->shininess), 1, 512, "%.1f");
    }

    std::vector<std::string> listTexture = _engine.GetResourcesManager().GetTextureNameList();
    listTexture.insert(listTexture.cbegin(), EMPTY_TEXTURE_STRING);

    std::string name = material->colorTexture.GetPath();
    if (SelectTexture(material->colorTexture, listTexture, name, "Color Texture"))
    {
        material->GenerateShader();
        _engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();
    }

    if (!material->checkLight)
        return;

    name = material->diffuseTexture.GetPath();
    if (SelectTexture(material->diffuseTexture, listTexture, name, "Diffuse Texture"))
    {
        material->GenerateShader();
        _engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();
    }

    name = material->specularTexture.GetPath();
    if (SelectTexture(material->specularTexture, listTexture, name, "Specular Texture"))
    {
        material->GenerateShader();
        _engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();
    }

    name = material->normalMap.GetPath();
    if (SelectTexture(material->normalMap, listTexture, name, "Normal Texture"))
    {
        material->GenerateShader();
        _engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();
    }
}

std::string
PropertiesWidget::SelectInList(const std::vector<std::string> &list, const std::string &currentlySelected,
                               const std::string &comboName)
{
    std::string selected = currentlySelected;

    std::string selectedName = currentlySelected;
    if (selectedName == "")
        selectedName = "NONE";

    if (ImGui::BeginCombo(comboName.c_str(), selectedName.c_str()))
    {
        for (const std::string &n : list)
        {
            bool isSelected = (currentlySelected == n);
            if (ImGui::Selectable(n.c_str(), isSelected))
            {
                selected = n;
                break;
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    return selected;

}

bool
PropertiesWidget::SelectTexture(Renderer::Texture &texture, const std::vector<std::string> &list,
                                const std::string &currentTexture,
                                const std::string &comboName)
{
    std::string selectedTexture = SelectInList(list, currentTexture, comboName);

    if (selectedTexture != currentTexture)
    {
        if (selectedTexture == EMPTY_TEXTURE_STRING)
            texture = Renderer::Texture();
        else
            texture = _engine.GetResourcesManager().LoadTexture(selectedTexture.c_str());
        return true;
    }
    return false;
}

void PropertiesWidget::DisplayTexture(const Resources::Asset *asset)
{
    auto *texture = (Renderer::Texture *) asset;
    //Renderer::Texture texture = _engine.GetResourcesManager().LoadTexture(_editor.assetName.c_str());
    ImVec2 wsize = ImGui::GetWindowSize();
    if (wsize.x < wsize.y)
        ImGui::Image((ImTextureID) (size_t) texture->GetID(), {wsize.x, wsize.x}, ImVec2(0, 1), ImVec2(1, 0));
    else
        ImGui::Image((ImTextureID) (size_t) texture->GetID(), {wsize.y, wsize.y}, ImVec2(0, 1), ImVec2(1, 0));

}

void PropertiesWidget::DisplayModel(const Resources::Asset *asset)
{
    Renderer::ModelRenderer &model = (*(Renderer::ModelRenderer *) asset);

    std::vector<std::string> listModelType;
    listModelType.emplace_back("CLASSIC");
    listModelType.emplace_back("NORMAL_MAP");
    listModelType.emplace_back("SKELETAL");

    std::string selected = SelectInList(listModelType, listModelType[(int) model.GetVertexType()],
                                        "Model Vertex Type");

    if (selected != listModelType[(int) model.GetVertexType()])
    {
        if (selected == "CLASSIC")
            _engine.GetResourcesManager().ReLoadModel(_editor.assetName, Renderer::VertexType::V_CLASSIC);
        else if (selected == "NORMAL_MAP")
            _engine.GetResourcesManager().ReLoadModel(_editor.assetName, Renderer::VertexType::V_NORMALMAP);
        else if (selected == "SKELETAL")
            _engine.GetResourcesManager().ReLoadModel(_editor.assetName, Renderer::VertexType::V_SKELETAL);
    }

}

void PropertiesWidget::DisplaySound(const Resources::Asset *asset)
{
    _engine.GetResourcesManager().LoadSound(_editor.assetName, Audio::SoundType::S_MASTER);
}

void PropertiesWidget::NameReader()
{
    auto &name = _engine.GetCurrentWorld().GetComponent<Name>(_editor.selectedEntity);
    ImGui::InputText("Name", &name.name);
}

void PropertiesWidget::TransformReader()
{

    ImGuiIO &io = ImGui::GetIO();
    auto &transform = _engine.GetCurrentWorld().GetComponent<Transform>(_editor.selectedEntity);

    if (!ImGui::CollapsingHeader("Transform"))
        return;

    ImGui::DragFloat3("Position", transform.position.e);
    ImGui::DragFloat3("Scale", transform.scale.e);
    bool isRotationChange = ImGui::DragFloat3("Rotation", _eulerRot.e);

    if (!ImGui::IsMouseDragging(0) && !isRotationChange)
        _eulerRot = transform.rotation.ToEuler() * RadToDeg<float>();
    if (isRotationChange)
        transform.rotation = Maths::Quaternion::EulerToQuaternion(_eulerRot * DegToRad<float>());
}

void PropertiesWidget::LightReader()
{
    auto &light = _engine.GetCurrentWorld().GetComponent<Component::Light>(_editor.selectedEntity);

    if (!ImGui::CollapsingHeader("Light"))
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
                        light.type = Component::LightType::L_POINT;
                        break;
                    case 1:
                        light.type = Component::LightType::L_DIRECTIONAL;
                        break;
                    case 2:
                        light.type = Component::LightType::L_SPOT;
                        break;

                }
                _engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();
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
        _engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();
    }
    if (light.type != Component::LightType::L_DIRECTIONAL)
    {
        if (ImGui::InputFloat("Linear Attenuation", &light.linear, 0.0f, 0.0f, "%.9f") ||
            ImGui::InputFloat("Quadratic Attenuation", &light.quadratic, 0.0f, 0.0f, "%.9f"))
        {
            _engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();
        }
    }
    if (light.type == Component::LightType::L_SPOT)
    {
        if (ImGui::DragFloat("Spot Angle", &light.spotAngle) ||
            ImGui::DragFloat("Outer Spot Angle", &light.outerSpotAngle))
        {
            _engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();
        }
    }

}

void PropertiesWidget::ModelReader()
{
    if (!ImGui::CollapsingHeader("Model"))
        return;


    auto& component = _engine.GetCurrentWorld().GetComponent<Component::Model>(_editor.selectedEntity);
    Renderer::ModelRenderer &model = component.model;

    std::vector<std::string> listModel = _engine.GetResourcesManager().GetModelNameList();

    if (ImGui::BeginCombo("##ModelCombo", model.GetName().c_str()))
    {
        for (auto &n : listModel)
        {
            bool isSelected = (model.GetPath() == n);
            if (ImGui::Selectable(n.c_str(), isSelected))
            {
                model = _engine.GetResourcesManager().LoadModel(n,Renderer::VertexType::V_CLASSIC);
                _engine.GetCurrentWorld().GetSystem<RenderSystem>()->SetMaterials();
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    ImGui::DragFloat3("Offset", component.offset.e, 0.1f);

    for (unsigned int i = 0; i < model.GetNumberMesh(); i++)
    {
        ImGui::SliderInt((std::string("Material Mesh ") + std::to_string(i + 1)).c_str(),
                         (int *) model.GetMeshMaterialIndex(i), 0, (int) model.GetNumberMaterial() - 1);
        _engine.GetCurrentWorld().GetSystem<RenderSystem>()->SetMaterials();
    }

    std::vector<std::string> listMaterial = _engine.GetResourcesManager().GetMaterialNameList();

    for (unsigned int i = 0; i < model.GetNumberMaterial(); i++)
    {
        if (ImGui::BeginCombo((std::string("##comboMaterial") + std::to_string(i)).c_str(),
                              model.GetMaterial(i)->GetName().c_str()))
        {
            for (auto &n : listMaterial)
            {
                bool isSelected = (model.GetPath() == n);
                if (ImGui::Selectable(n.c_str(), isSelected))
                {
                    Renderer::MaterialInterface materialInterface = _engine.GetResourcesManager().LoadMaterial(
                            n.c_str());
                    model.ChangeMaterial(materialInterface, i);
                    _engine.GetCurrentWorld().GetSystem<RenderSystem>()->SetMaterials();
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
    }
    if (ImGui::Button("Add Material"))
        model.AddMaterial(_engine.GetResourcesManager().LoadMaterial(DEFAULT_MATERIAL_STRING));
    ImGui::SameLine();
    if (ImGui::Button("Remove Material"))
        model.RemoveMaterial(model.GetNumberMaterial() - 1);
}

void PropertiesWidget::AnimatorReader()
{
    if (ImGui::CollapsingHeader("Animator"))
        return;

    auto &animator = _engine.GetCurrentWorld().GetComponent<Component::Animator>(_editor.selectedEntity);

    std::vector<std::string> listAnimation = _engine.GetResourcesManager().GetAnimationNameList();

    if (ImGui::BeginCombo("##AnimatorCombo", animator.GetAnimation().GetName().c_str()))
    {
        for (auto &n : listAnimation)
        {
            bool isSelected = (animator.GetAnimation().GetPath() == n);
            if (ImGui::Selectable(n.c_str(), isSelected))
            {
                animator.SetAnimation((_engine.GetResourcesManager().LoadAnimation(n)));
                _engine.GetCurrentWorld().GetSystem<RenderSystem>()->SetMaterials();
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
}


void PropertiesWidget::CameraReader()
{
    auto &camera = _engine.GetCurrentWorld().GetComponent<Camera>(_editor.selectedEntity);
    if (!ImGui::CollapsingHeader("Camera"))
        return;

    ImGui::Checkbox("Is perspective", &camera._isPerspective);
    float fov = camera._fov * RadToDeg<float>();
    ImGui::DragFloat("FOV", &fov, 1.f, 0.f, 180.f);
    {
        camera._fov = fov * DegToRad<float>();
    }

    ImGui::DragFloat("Near", &camera._near, 1.f, 0.01, camera._far);
    ImGui::DragFloat("Far", &camera._far, 1.f, camera._near, 180.f);
}

void PropertiesWidget::RigidBodyReader()
{
    if (!ImGui::CollapsingHeader("RigidBody"))
        return;

    auto &rigidBody = _engine.GetCurrentWorld().GetComponent<RigidBody>(_editor.selectedEntity);

    RigidBodyChangeBodyType(rigidBody);
    RigidBodyResizeShape(rigidBody);
    RigidBodySetIsTrigger(rigidBody);
    RigidBodySetIsGravityEnabled(rigidBody);
    RigidBodySetMass(rigidBody);
    RigidBodySetBounciness(rigidBody);
}

void PropertiesWidget::AddComponent()
{
    World &world = _engine.GetCurrentWorld();
    if (ImGui::Button("Add Component"))
    {
        ImGui::OpenPopup("##ComponentContextMenu_Add");
    }

    if (ImGui::BeginPopup("##ComponentContextMenu_Add"))
    {
        //Camera
        if (!world.HasComponent<Camera>(_editor.selectedEntity) && ImGui::MenuItem("Camera"))
        {
            world.AddComponent(_editor.selectedEntity, Component::Camera(1280, 720, 1000, -1, 20 * 3.1415 / 180));
        }
            //Light
        if (!world.HasComponent<Light>(_editor.selectedEntity) && ImGui::BeginMenu("Light"))
        {
            AddLight();
            ImGui::EndMenu();
        }

        if (!world.HasComponent<Model>(_editor.selectedEntity) && ImGui::BeginMenu("Model"))
        {
            std::vector<std::string> listModel = _engine.GetResourcesManager().GetModelNameList();
            for (const auto &n : listModel)
            {
                if (ImGui::MenuItem(n.c_str()))
                {
                    Component::Model model;
                    model.model = _engine.GetResourcesManager().LoadModel(n,
                                                                          Renderer::VertexType::V_NORMALMAP);
                    world.AddComponent(_editor.selectedEntity, model);
                }
            }
            ImGui::EndMenu();
        }

        if (!world.HasComponent<CharacterController>(_editor.selectedEntity) && ImGui::MenuItem("Character controller"))
            world.AddComponent(_editor.selectedEntity, CharacterController());
        if (!world.HasComponent<PlayerComponent>(_editor.selectedEntity) && ImGui::MenuItem("Player component"))
            world.AddComponent(_editor.selectedEntity, PlayerComponent());
        if (!world.HasComponent<CameraGameplay>(_editor.selectedEntity) && ImGui::MenuItem("Camera gameplay"))
            world.AddComponent(_editor.selectedEntity, CameraGameplay());
        if(world.HasComponent<Transform>(_editor.selectedEntity))
            AddRigidBody(); // Propose to add a RigidBody only if the entity already have a Transform
        if (!world.HasComponent<Animator>(_editor.selectedEntity) && ImGui::MenuItem("Animator"))
            world.AddComponent(_editor.selectedEntity, Animator());
        if (!world.HasComponent<ParticleEmitter>(_editor.selectedEntity) && ImGui::MenuItem("Particle Emitter"))
            world.AddComponent(_editor.selectedEntity, ParticleEmitter());
        if (!world.HasComponent<SimpleShadow>(_editor.selectedEntity) && ImGui::MenuItem("Simple Shadow"))
            world.AddComponent(_editor.selectedEntity, SimpleShadow());

        ImGui::EndPopup();
    }

}

void PropertiesWidget::AddLight()
{
    World &world = _engine.GetCurrentWorld();

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
        light.type = Component::LightType::L_DIRECTIONAL;
        world.AddComponent(_editor.selectedEntity, light);
    }
    else if (ImGui::MenuItem("Point"))
    {
        light.type = Component::LightType::L_POINT;
        world.AddComponent(_editor.selectedEntity, light);
    }
    else if (ImGui::MenuItem("Spot"))
    {
        light.type = Component::LightType::L_SPOT;
        world.AddComponent(_editor.selectedEntity, light);
    }
}

void PropertiesWidget::DeleteComponent()
{
    World &world = _engine.GetCurrentWorld();
    if (ImGui::Button("Delete Component"))
    {
        ImGui::OpenPopup("##ComponentContextMenu_Delete");
    }

    if (ImGui::BeginPopup("##ComponentContextMenu_Delete"))
    {
        if (world.HasComponent<Camera>(_editor.selectedEntity) && ImGui::MenuItem("Camera"))
            world.RemoveComponent<Camera>(_editor.selectedEntity);
        if (world.HasComponent<Light>(_editor.selectedEntity) && ImGui::MenuItem("Light"))
            world.RemoveComponent<Light>(_editor.selectedEntity);
        if (world.HasComponent<Model>(_editor.selectedEntity) && ImGui::MenuItem("Model"))
            world.RemoveComponent<Model>(_editor.selectedEntity);
        if (world.HasComponent<RigidBody>(_editor.selectedEntity) && ImGui::MenuItem("Rigidbody"))
            world.RemoveComponent<RigidBody>(_editor.selectedEntity);
        if (world.HasComponent<CharacterController>(_editor.selectedEntity) && ImGui::MenuItem("Character Controller"))
            world.RemoveComponent<CharacterController>(_editor.selectedEntity);
        if (world.HasComponent<PlayerComponent>(_editor.selectedEntity) && ImGui::MenuItem("Player component"))
            world.RemoveComponent<PlayerComponent>(_editor.selectedEntity);
        if (world.HasComponent<CameraGameplay>(_editor.selectedEntity) && ImGui::MenuItem("Camera gameplay"))
            world.RemoveComponent<CameraGameplay>(_editor.selectedEntity);
        if (world.HasComponent<ParticleEmitter>(_editor.selectedEntity) && ImGui::MenuItem("ParticleEmitter"))
            world.RemoveComponent<ParticleEmitter>(_editor.selectedEntity);
        if (world.HasComponent<SimpleShadow>(_editor.selectedEntity) && ImGui::MenuItem("Simple Shadow"))
            world.RemoveComponent<SimpleShadow>(_editor.selectedEntity);
        ImGui::EndPopup();
    }
}

void PropertiesWidget::AddRigidBody()
{
    if (ImGui::BeginMenu("RigidBody"))
    {
        World &world = _engine.GetCurrentWorld();
        if (ImGui::MenuItem("Box collider"))
        {
            world.AddComponent(_editor.selectedEntity, RigidBody());
            PhysicsSystem::SetRigidBody(_editor.selectedEntity);
            PhysicsSystem::SetType(_editor.selectedEntity, BodyType::STATIC);
            PhysicsSystem::AddBoxCollider(_editor.selectedEntity, {1.0f, 1.0f, 1.0f});
        }
        if (ImGui::MenuItem("Sphere collider"))
        {
            world.AddComponent(_editor.selectedEntity, RigidBody());
            PhysicsSystem::SetRigidBody(_editor.selectedEntity);
            PhysicsSystem::SetType(_editor.selectedEntity, BodyType::STATIC);
            PhysicsSystem::AddSphereCollider(_editor.selectedEntity, 1.f);

        }
        if (ImGui::MenuItem("Capsule collider"))
        {
            world.AddComponent(_editor.selectedEntity, RigidBody());
            PhysicsSystem::SetRigidBody(_editor.selectedEntity);
            PhysicsSystem::SetType(_editor.selectedEntity, BodyType::STATIC);
            PhysicsSystem::AddCapsuleCollider(_editor.selectedEntity, 1.f, 1.0f);
        }
        ImGui::EndMenu();
    }
}

void PropertiesWidget::RigidBodyChangeBodyType(Component::RigidBody &rigidBody)
{
    const char *enumBodyType[]{"Static", "Kinematic", "Dynamic"};
    int bodyType = (int) rigidBody.GetBodyType();
    if (ImGui::Combo("BodyType", &bodyType, enumBodyType, IM_ARRAYSIZE(enumBodyType)))
    {
        switch (bodyType)
        {
            case 0:
            {
                if (rigidBody.GetBodyType() != BodyType::STATIC)
                    PhysicsSystem::SetType(_editor.selectedEntity, BodyType::STATIC);

                break;
            }
            case 1:
            {
                if (rigidBody.GetBodyType() != BodyType::KINEMATIC)
                    PhysicsSystem::SetType(_editor.selectedEntity, BodyType::KINEMATIC);

                break;
            }
            case 2:
            {
                if (rigidBody.GetBodyType() != BodyType::DYNAMIC)
                    PhysicsSystem::SetType(_editor.selectedEntity, BodyType::DYNAMIC);

                break;
            }
            default:
                break;
        }
    }
}

void PropertiesWidget::RigidBodyResizeShape(Component::RigidBody &rigidBody)
{
    if (rigidBody.GetCollisionShapeType() == CollisionShapeType::CONVEX_POLYHEDRON)
    {
        Maths::Vector3<float> halfExtend = rigidBody.GetHalfExtends();
        if (ImGui::DragFloat3("Half extend", halfExtend.e))
            PhysicsSystem::ResizeBoxCollider(_editor.selectedEntity, halfExtend);
    }
    if (rigidBody.GetCollisionShapeType() == CollisionShapeType::SPHERE)
    {
        float radius = rigidBody.GetRadius();
        if (ImGui::DragFloat("Radius", &radius, 0.1f, 0.001f, FLT_MAX))
            PhysicsSystem::ResizeSphereCollider(_editor.selectedEntity, radius);
    }
    if (rigidBody.GetCollisionShapeType() == CollisionShapeType::CAPSULE)
    {
        float radius = rigidBody.GetRadius();
        float height = rigidBody.GetHeight();

        if (ImGui::DragFloat("Radius", &radius, 0.1f, 0.001f, FLT_MAX)
            || ImGui::DragFloat("height", &height, 0.1f, 0.001f, FLT_MAX))
        {
            PhysicsSystem::ResizeCapsuleCollider(_editor.selectedEntity, radius, height);
        }
    }
}

void PropertiesWidget::RigidBodySetIsTrigger(Component::RigidBody &rigidBody)
{
    bool isTrigger = rigidBody.GetIsTrigger();
    if (ImGui::Checkbox("Trigger", &isTrigger))
        PhysicsSystem::SetIsTrigger(_editor.selectedEntity, isTrigger);

}

void PropertiesWidget::RigidBodySetMass(RigidBody &rigidBody)
{
    float mass = rigidBody.GetMass();
    if (ImGui::DragFloat("mass", &mass))
    {
        PhysicsSystem::SetMass(_editor.selectedEntity, mass);
    }
}

void PropertiesWidget::RigidBodySetIsGravityEnabled(RigidBody &rigidBody)
{
    bool isGravityEnabled = rigidBody.GetIsGravityEnabled();
    if (ImGui::Checkbox("Gravity Enabled", &isGravityEnabled))
        PhysicsSystem::SetIsGravityEnable(_editor.selectedEntity, isGravityEnabled);
}

void PropertiesWidget::RigidBodySetBounciness(RigidBody &rigidBody)
{
    float bounciness = rigidBody.GetBounciness();
    if (ImGui::DragFloat("Bounciness", &bounciness, 0.1f, 0.0f, 1.0f))
        PhysicsSystem::SetBounciness(_editor.selectedEntity, bounciness);
}

void PropertiesWidget::CharacterControllerReader()
{
    if (!ImGui::CollapsingHeader("Character controller"))
        return;
    auto &characterController = _engine.GetCurrentWorld().GetComponent<CharacterController>(_editor.selectedEntity);
    ImGui::DragFloat("Speed", &characterController.speed);
}

void PropertiesWidget::CameraGameplayReader()
{
    if (!ImGui::CollapsingHeader("Camera Gameplay"))
        return;
    auto &cameraController = _engine.GetCurrentWorld().GetComponent<CameraGameplay>(_editor.selectedEntity);
    ImGui::DragFloat3("Distance", cameraController.distance.e);
}

void PropertiesWidget::ParticleReader()
{
    if (!ImGui::CollapsingHeader("Particle Emitter"))
        return;

    auto& particleEmitter = _engine.GetCurrentWorld().GetComponent<ParticleEmitter>(_editor.selectedEntity);

    if(ImGui::TreeNode("Color##Particle"))
    {
        ImGui::ColorEdit4("Start", particleEmitter.ColorStart().e);
        ImGui::ColorEdit4("End", particleEmitter.ColorEnd().e);
        ImGui::TreePop();
    }

    if(ImGui::TreeNode("Length##Particle"))
    {
        ImGui::DragFloat("Start", &particleEmitter.LengthStart(),0.1f,0.f);
        ImGui::DragFloat("End", &particleEmitter.LengthEnd(),0.1f,0.f);
        ImGui::TreePop();
    }
    if(ImGui::TreeNode("Angle##Particle"))
    {
        ImGui::SliderAngle("Start", &particleEmitter.AngleStart());
        ImGui::SliderAngle("End", &particleEmitter.AngleEnd());
        ImGui::TreePop();
    }
    float duration = particleEmitter.GetDuration();
    if (ImGui::DragFloat("Duration", &duration, 0.1f,0.f,60.f))
        particleEmitter.SetDuration(duration);

    int size = particleEmitter.GetSize();
    if (ImGui::DragInt("Number", &size, 1, 1, INT32_MAX))
        particleEmitter.SetSize(size);

    Renderer::Texture& texture = particleEmitter.GetTexture();
    std::vector<std::string> listTexture = _engine.GetResourcesManager().GetTextureNameList();
    listTexture.insert(listTexture.begin(), "NONE");

    if (ImGui::BeginCombo("Texture", texture.GetName().c_str()))
    {
        for (auto &n : listTexture)
        {
            bool isSelected = (texture.GetPath() == n);
            if (ImGui::Selectable(n.c_str(), isSelected))
            {
                if (n == "NONE")
                    texture = Renderer::Texture();
                else
                    texture = _engine.GetResourcesManager().LoadTexture(n.c_str());
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
}

const char* listShadowType[2] = {"SQUARE", "CIRCLE"};

void PropertiesWidget::SimpleShadowReader()
{
    if (!ImGui::CollapsingHeader("Simple Shadow"))
        return;

    auto& shadow = _engine.GetCurrentWorld().GetComponent<SimpleShadow>(_editor.selectedEntity);

    if (ImGui::BeginCombo("Shadow Type", listShadowType[shadow.type]))
    {
        for (unsigned int i = 0; i < 2 ; i++)
        {
            bool isSelected = (listShadowType[shadow.type] == listShadowType[i]);
            if (ImGui::Selectable(listShadowType[i], isSelected))
            {
                shadow.type = (SimpleShadow::ShadowType)i;
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::DragFloat2("Scale ##Shadow", shadow.scale.e, 0.1f, FLT_MIN, FLT_MAX);
    ImGui::DragFloat3("Offset ##Shadow", shadow.offset.e, 0.1f);

    float degAngle = shadow.yRotation * RadToDeg<float>();
    ImGui::DragFloat("Angle", &degAngle);
    shadow.yRotation = degAngle * DegToRad<float>();
}