//
// Created by g.nisi on 3/10/21.
//

#ifndef QUACKENGINE_PROPERTIESWIDGET_HPP
#define QUACKENGINE_PROPERTIESWIDGET_HPP

#include "Widgets/Widget.hpp"


class PropertiesWidget : public Widget
{
public:
    void UpdateAlways() final;

    void UpdateVisible() final;

    void OnShow() final;

    void OnHide() final;
};


#endif //QUACKENGINE_PROPERTIESWIDGET_HPP
