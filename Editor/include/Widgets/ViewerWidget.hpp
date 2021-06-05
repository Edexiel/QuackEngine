#ifndef QUACKENGINE_VIEWERWIDGET_HPP
#define QUACKENGINE_VIEWERWIDGET_HPP

#include "Widgets/Widget.hpp"

class ViewerWidget : public Widget
{
public:
    explicit ViewerWidget(Editor &editor);

    void UpdateVisible() final;
    void AddEntity();
    void DestroyEntity();
    void DuplicateEntity();
};

#endif //QUACKENGINE_VIEWERWIDGET_HPP