#ifndef QUACKENGINE_PROPERTIESWIDGET_HPP
#define QUACKENGINE_PROPERTIESWIDGET_HPP

#include "Widgets/Widget.hpp"

class PropertiesWidget : public Widget
{
public:
    PropertiesWidget();
    void UpdateVisible() final;

private:
    static void NameReader();
    static void TransformReader();
    static void LightReader();
    static void ModelReader();
    static void CameraReader();
    static void RigidBodyReader();
    static void AddComponent();
    static void DeleteComponent();

    static void AddLight();


};


#endif //QUACKENGINE_PROPERTIESWIDGET_HPP
