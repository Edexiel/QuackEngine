//
// Created by g.nisi on 3/10/21.
//

#ifndef QUACKENGINE_EXPLORERWIDGET_HPP
#define QUACKENGINE_EXPLORERWIDGET_HPP

#include "Widgets/Widget.hpp"

class ExplorerWidget : public Widget
{
private:
    unsigned int _selected;

public:
    ExplorerWidget();

    void UpdateVisible() final;

};


#endif //QUACKENGINE_EXPLORERWIDGET_HPP
