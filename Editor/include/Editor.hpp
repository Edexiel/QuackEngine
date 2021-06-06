#ifndef QUACKENGINE_EDITOR_HPP
#define QUACKENGINE_EDITOR_HPP

#include "CameraEditor.hpp"

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
    CameraEditor camera = CameraEditor(1280, 720, 5000.f, 0.01f, 3.1415f * 60 / 180.f);

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
