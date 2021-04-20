//
// Created by g.nisi on 3/10/21.
//

#ifndef QUACKENGINE_PROPERTIESWIDGET_HPP
#define QUACKENGINE_PROPERTIESWIDGET_HPP

#include "Widgets/Widget.hpp"

struct Transform;

class PropertiesWidget : public Widget
{
public:
    PropertiesWidget();

    void UpdateVisible() final;
    void TransformReader() const;
    void LightReader() const;
    void ModelReader() const;
    void AddComponent();

private:
      void AddLight();

};


#endif //QUACKENGINE_PROPERTIESWIDGET_HPP
