#ifndef QUACKENGINE_VIEWERWIDGET_HPP
#define QUACKENGINE_VIEWERWIDGET_HPP

#include "Widgets/Widget.hpp"

class ViewerWidget : public Widget
{
private:
    int _selected = -1;
public:
    ViewerWidget();

    void UpdateVisible() final;
    void AddEntity();
    void DestroyEntity() const;
};

#endif //QUACKENGINE_VIEWERWIDGET_HPP