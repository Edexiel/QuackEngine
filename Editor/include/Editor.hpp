#ifndef QUACKENGINE_EDITOR_HPP
#define QUACKENGINE_EDITOR_HPP

#include <vector>

#include "Widgets/Widget.hpp"
#include "GLFW/glfw3.h"


class Editor
{
private:
    GLFWwindow *window;

    std::vector<Widget> _widgets;
public:
    Editor();
    ~Editor();

    int Init();
    void InitImGUI();
};


#endif //QUACKENGINE_EDITOR_HPP
