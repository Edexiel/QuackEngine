#ifndef QUACKENGINE_PROPERTIESWIDGET_HPP
#define QUACKENGINE_PROPERTIESWIDGET_HPP

#include "Widgets/Widget.hpp"

class PropertiesWidget : public Widget
{
public:
    PropertiesWidget();

    void UpdateVisible() final;
    void TransformReader() const;
    void AddComponent();

};


#endif //QUACKENGINE_PROPERTIESWIDGET_HPP
