//
// Created by g.nisi on 3/9/21.
//

#ifndef QUACKENGINE_ENGINE_HPP
#define QUACKENGINE_ENGINE_HPP

#include <GLFW/glfw3.h>

enum GLProfile
{
    ANY = GLFW_OPENGL_ANY_PROFILE,
    CORE = GLFW_OPENGL_CORE_PROFILE,
    COMPAT = GLFW_OPENGL_COMPAT_PROFILE
};


struct Gl
{
    int major;
    int minor;
    bool debug;
    GLProfile profile;
};

struct Window
{
    enum class Mode
    {
        WINDOWED,
        FULLSCREEN,
        WINDOWED_FULLSCREEN,
    };
    const char *title{};
    int size[2]{};
    Mode mode{};
    int monitor = 0;
};

struct EngineSettings
{
    Gl gl{};
    Window window;
};

class Engine
{
private:
    bool _init = false;
    GLFWwindow *_window= nullptr;
public:
    GLFWwindow *getWindow() const;
public:
    bool isInit() const;
public:
    Engine() = default;
    ~Engine() = default;

    int init(EngineSettings &settings);
};


#endif //QUACKENGINE_ENGINE_HPP
