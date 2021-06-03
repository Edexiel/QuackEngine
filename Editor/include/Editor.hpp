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
    static void InitImGui(struct GLFWwindow *window);
    static void SetStyle();
    static void SetIo();

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

inline Engine &Editor::GetEngine() const
{
    return _engine;
}

#endif //QUACKENGINE_EDITOR_HPP
