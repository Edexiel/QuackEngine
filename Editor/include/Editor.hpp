#ifndef QUACKENGINE_EDITOR_HPP
#define QUACKENGINE_EDITOR_HPP

#include <vector>
#include <memory>
#include <string>

class Editor
{
private:
    std::vector<std::unique_ptr<class Widget>> _widgets;
    std::unique_ptr<class Widget> _menuBar;

    class Engine &_engine;

    void InitWidgets();
    void InitImGui(class GLFWwindow *window);
    void SetStyle();
    void SetIo();

public:
    /*** Selection ***/
    std::int32_t selectedEntity = 0;
    bool showProperties{true};
    std::string assetName;

    explicit Editor();
    ~Editor();
    void Draw();
    Engine &GetEngine() const;
};


#endif //QUACKENGINE_EDITOR_HPP
