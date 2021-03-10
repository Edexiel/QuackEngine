//
// Created by g.nisi on 3/10/21.
//

#ifndef QUACKENGINE_VIEWPORTWIDGET_HPP
#define QUACKENGINE_VIEWPORTWIDGET_HPP

#include "Widgets/Widget.hpp"


class ViewportWidget: public Widget
{
public:
    void draw() override final;
    void update() override final;
};


#endif //QUACKENGINE_VIEWPORTWIDGET_HPP
