#ifndef QUACKENGINE_TOOLBOXWIDGET_HPP
#define QUACKENGINE_TOOLBOXWIDGET_HPP

#include "Widgets/Widget.hpp"


class ToolboxWidget : public Widget
{
private:

    class Engine &_engine;

    bool isPlaying = false;
    void Save();
    void Reload();
public:
    ToolboxWidget();
    void UpdateVisible() final;
};


#endif //QUACKENGINE_TOOLBOXWIDGET_HPP
