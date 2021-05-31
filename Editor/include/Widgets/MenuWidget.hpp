#ifndef QUACKENGINE_MENUWIDGET_HPP
#define QUACKENGINE_MENUWIDGET_HPP

#include "Widgets/Widget.hpp"

class MenuWidget : public Widget
{
public:
    explicit MenuWidget(Editor &editor);
public:
    void UpdateVisible() override;
    void Draw() final;
};

#endif //QUACKENGINE_MENUWIDGET_HPP
