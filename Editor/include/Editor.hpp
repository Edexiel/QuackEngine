#ifndef QUACKENGINE_EDITOR_HPP
#define QUACKENGINE_EDITOR_HPP

#include <vector>
#include <memory>

class Editor
{
private:
    std::vector<std::unique_ptr<class Widget>> _widgets;

    void InitWidgets();
    void InitImGui();
public:

    explicit Editor();
    ~Editor();
    void Draw();
};


#endif //QUACKENGINE_EDITOR_HPP
