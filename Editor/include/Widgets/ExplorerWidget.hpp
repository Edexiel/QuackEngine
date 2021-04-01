//
// Created by g.nisi on 3/10/21.
//

#ifndef QUACKENGINE_EXPLORERWIDGET_HPP
#define QUACKENGINE_EXPLORERWIDGET_HPP

#include "Widgets/Widget.hpp"

class ExplorerWidget : public Widget
{
public:

    void UpdateAlways() final;

    void UpdateVisible() final;

    void OnShow() final;

    void OnHide() final;
};


#endif //QUACKENGINE_EXPLORERWIDGET_HPP
