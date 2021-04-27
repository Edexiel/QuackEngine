#ifndef QUACKENGINE_PROPERTIESWIDGET_HPP
#define QUACKENGINE_PROPERTIESWIDGET_HPP

#include "Widgets/Widget.hpp"
#include "Maths/Vector3.hpp"

class PropertiesWidget : public Widget
{
public:
    PropertiesWidget();
    void UpdateVisible() final;

private:
    static void NameReader();
    void TransformReader();
    static void LightReader();
    static void ModelReader();
    static void CameraReader();
    static void RigidBodyReader();
    static void AddComponent();
    static void DeleteComponent();

    static void AddLight();

    Entity _previousEntity{0};
    Maths::Vector3f _previousEulerRot{0,0,0};
    Maths::Vector3f _eulerRot{0,0,0};


};


#endif //QUACKENGINE_PROPERTIESWIDGET_HPP
