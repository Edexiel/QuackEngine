//
// Created by g.nisi on 3/10/21.
//

#ifndef QUACKENGINE_SCENEWIDGET_HPP
#define QUACKENGINE_SCENEWIDGET_HPP

#include "Widgets/Widget.hpp"


class SceneWidget: public Widget
{
public:
    void draw() override final;
    void update() override final;
};


#endif //QUACKENGINE_SCENEWIDGET_HPP
