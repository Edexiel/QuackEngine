#ifndef QUACKENGINE_EDITOR_HPP
#define QUACKENGINE_EDITOR_HPP

#include <vector>
#include <memory>
#include <string>

#include "Widgets/Widget.hpp"
#include "GLFW/glfw3.h"
#include "Engine.hpp"

enum class WINDOW_MODE
{
    WINDOWED,
    FULLSCREEN,
    WINDOWED_FULLSCREEN,
};
struct EngineSettings
{
    bool debug{};
    std::string windowTitle{};
    int windowSize[2]{};
    WINDOW_MODE mode{};
    int monitor = 0;
};

class Editor
{
private:
    Engine &_engine;

    GLFWwindow *_window = nullptr;

    std::vector<std::unique_ptr<Widget>> _widgets;

    void InitGlfw(const EngineSettings &settings);

    void InitWidgets();

    void InitImGui();

public:

    explicit Editor(Engine &engine);

    ~Editor();

    void Init(const EngineSettings &settings);

    void Draw();

    GLFWwindow *GetWindow() const;
};


#endif //QUACKENGINE_EDITOR_HPP
