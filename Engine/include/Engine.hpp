//
// Created by g.nisi on 3/9/21.
//

#ifndef QUACKENGINE_ENGINE_HPP
#define QUACKENGINE_ENGINE_HPP

#include <GLFW/glfw3.h>
#include <exception>

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

struct GLFW_Initialization_error : public std::exception
{
    const char *what() const noexcept override
    {
        return "GLFW was not correctly initialized, aborting";
    }
};

struct GLFW_Window_Initialization_error : public std::exception
{
    const char *what() const noexcept override
    {
        return "GLFW's window was not correctly initialized, aborting";
    }
};

struct GLFW_Window_Initialization_error : public std::exception
{
    const char *what() const noexcept override
    {
        return "GLFW's window was not correctly initialized, aborting";
    }
};

class Engine
{
private:
    bool _init = false;
    GLFWwindow *_window = nullptr;
public:
    GLFWwindow *getWindow() const;
public:
    bool isInit() const;
public:
    Engine() = delete;
    Engine(const EngineSettings &settings);
    ~Engine() = default;
};


#endif //QUACKENGINE_ENGINE_HPP
