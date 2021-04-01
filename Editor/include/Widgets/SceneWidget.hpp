//
// Created by g.nisi on 3/10/21.
//

#ifndef QUACKENGINE_SCENEWIDGET_HPP
#define QUACKENGINE_SCENEWIDGET_HPP

#include "Widgets/Widget.hpp"


class SceneWidget: public Widget
{
public:
    void UpdateAlways() final;

    void UpdateVisible() final;

    void OnShow() final;

    void OnHide() final;
};


#endif //QUACKENGINE_SCENEWIDGET_HPP
