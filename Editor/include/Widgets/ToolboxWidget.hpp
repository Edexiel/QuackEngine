#ifndef QUACKENGINE_TOOLBOXWIDGET_HPP
#define QUACKENGINE_TOOLBOXWIDGET_HPP

#include "Widgets/Widget.hpp"


class ToolboxWidget : public Widget
{
private:
    bool isPlaying = false;
    void Save();
    void Reload();
public:
    explicit ToolboxWidget(Editor &editor);
    void UpdateVisible() final;
};


#endif //QUACKENGINE_TOOLBOXWIDGET_HPP
