#ifndef QUACKENGINE_PROPERTIESWIDGET_HPP
#define QUACKENGINE_PROPERTIESWIDGET_HPP

#include "Widgets/Widget.hpp"

class PropertiesWidget : public Widget
{
public:
    PropertiesWidget();
    void UpdateVisible() final;

private:
    void NameReader() const;
    void TransformReader() const;
    void LightReader() const;
    void CameraReader() const;
    void RigidBodyReader() const;
    void AddComponent();
    void DeleteComponent();

};


#endif //QUACKENGINE_PROPERTIESWIDGET_HPP
