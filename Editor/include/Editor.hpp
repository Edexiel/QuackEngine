#ifndef QUACKENGINE_EDITOR_HPP
#define QUACKENGINE_EDITOR_HPP

#include <vector>
#include "Widgets/Widget.hpp"
class Editor
{
private:
    std::vector<Widget> _widgets;
public:
    Editor();
    ~Editor();
};


#endif //QUACKENGINE_EDITOR_HPP
