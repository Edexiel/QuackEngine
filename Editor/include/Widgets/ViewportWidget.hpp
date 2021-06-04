//
// Created by g.nisi on 3/10/21.
//

#ifndef QUACKENGINE_VIEWPORTWIDGET_HPP
#define QUACKENGINE_VIEWPORTWIDGET_HPP

#include "Widgets/Widget.hpp"


class ViewportWidget : public Widget
{
private:
    bool _isInGame {false};
public:
    ViewportWidget(Editor &editor);

//    void UpdateAlways() override;

    void UpdateVisible() override;
    void LockCursor();

//    void OnShow() override;

//    void OnHide() override;
};


#endif //QUACKENGINE_VIEWPORTWIDGET_HPP
