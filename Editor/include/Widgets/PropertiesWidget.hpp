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
    void AddComponent();

};


#endif //QUACKENGINE_PROPERTIESWIDGET_HPP
