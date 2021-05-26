//
// Created by gnisi on 24/05/2021.
//

#ifndef QUACKENGINE_TOOLBOXWIDGET_HPP
#define QUACKENGINE_TOOLBOXWIDGET_HPP

#include "Widgets/Widget.hpp"

class ToolboxWidget :public Widget
{
private:
    bool isPlaying=false;
public:
    ToolboxWidget();
    void UpdateVisible() final;
};


#endif //QUACKENGINE_TOOLBOXWIDGET_HPP
