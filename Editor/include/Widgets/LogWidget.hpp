//
// Created by g.nisi on 3/10/21.
//

#ifndef QUACKENGINE_LOGWIDGET_HPP
#define QUACKENGINE_LOGWIDGET_HPP

#include "Widgets/Widget.hpp"


class LogWidget: public Widget
{
public:
    void UpdateAlways() final;

    void UpdateVisible() final;

    void OnShow() final;

    void OnHide() final;
};


#endif //QUACKENGINE_LOGWIDGET_HPP
