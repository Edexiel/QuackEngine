#ifndef QUACKENGINE_EDITOR_HPP
#define QUACKENGINE_EDITOR_HPP

#include <vector>

#include "Widgets/Widget.hpp"
#include "GLFW/glfw3.h"
#include <memory>

class Editor
{
private:
    GLFWwindow *window= nullptr;

    std::vector<std::unique_ptr<Widget>> _widgets;
public:
    Editor() = default;
    ~Editor() = default;

    int initWidgets();
    void initImGUI();
    void update();
    void draw();
};


#endif //QUACKENGINE_EDITOR_HPP
