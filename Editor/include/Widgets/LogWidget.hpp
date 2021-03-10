//
// Created by g.nisi on 3/10/21.
//

#ifndef QUACKENGINE_LOGWIDGET_HPP
#define QUACKENGINE_LOGWIDGET_HPP

#include "Widgets/Widget.hpp"


class LogWidget: public Widget
{
public:
    void draw() override final;
    void update() override final;
};


#endif //QUACKENGINE_LOGWIDGET_HPP
