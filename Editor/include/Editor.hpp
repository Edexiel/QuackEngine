#ifndef QUACKENGINE_EDITOR_HPP
#define QUACKENGINE_EDITOR_HPP

#include <vector>
#include <memory>
#include "GLFW/glfw3.h"


class Editor
{
private:
    std::vector<std::unique_ptr<class Widget>> _widgets;

    void InitWidgets();
    void InitImGui(GLFWwindow * window);
    void SetStyle();
    void SetIo();
public:

    explicit Editor(GLFWwindow * window);
    ~Editor();
    void Draw();
};


#endif //QUACKENGINE_EDITOR_HPP
