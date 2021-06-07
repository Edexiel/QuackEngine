#ifndef QUACKENGINE_PROPERTIESWIDGET_HPP
#define QUACKENGINE_PROPERTIESWIDGET_HPP

#include "Widgets/Widget.hpp"
#include "Maths/Vector3.hpp"


namespace Component
{
    class RigidBody;
}
namespace Renderer
{
    class Texture;
}
namespace Resources
{
    class Asset;
}

class PropertiesWidget : public Widget
{
public:
    explicit PropertiesWidget(Editor &editor);
    void UpdateVisible() final;

private:
    Maths::Vector3f _eulerRot{0, 0, 0};

    void ShowComponents();
    void ShowAssets();

    void NameReader();
    void TransformReader();
    void LightReader();
    void ModelReader();
    void AnimatorReader();
    void CameraReader();
    void RigidBodyReader();
    void CharacterControllerReader();
    void CameraGameplayReader();
    void ParticleReader();
    void SimpleShadowReader();
    void SwitchSceneTriggerReader();
    void EnemySpawnReader();


    void AddComponent();
    void DeleteComponent();

    void AddLight();
    void AddRigidBody();

    void RigidBodyChangeBodyType(Component::RigidBody &rigidBody);
    void RigidBodyResizeShape(Component::RigidBody &rigidBody);
    void RigidBodySetIsTrigger(Component::RigidBody &rigidBody);
    void RigidBodySetMass(Component::RigidBody &rigidBody);
    void RigidBodySetIsGravityEnabled(Component::RigidBody &rigidBody);
    void RigidBodySetBounciness(Component::RigidBody &rigidBody);

    void DisplayMaterial(const Resources::Asset *asset);
    void DisplayTexture(const Resources::Asset *asset);
    void DisplayModel(const Resources::Asset *asset);
    void DisplaySound(const Resources::Asset *asset);

    std::string
    SelectInList(const std::vector<std::string> &list, const std::string &currentlySelected,
                 const std::string &comboName);
    bool
    SelectTexture(Renderer::Texture &texture, const std::vector<std::string> &list, const std::string &currentTexture,
                  const std::string &comboName);
};


#endif //QUACKENGINE_PROPERTIESWIDGET_HPP
