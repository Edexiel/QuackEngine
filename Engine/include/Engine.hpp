//
// Created by g.nisi on 3/9/21.
//

#ifndef QUACKENGINE_ENGINE_HPP
#define QUACKENGINE_ENGINE_HPP

#include <GLFW/glfw3.h>
#include <exception>

enum class WindowMode
{
    WINDOWED,
    FULLSCREEN,
    WINDOWED_FULLSCREEN,
};
struct EngineSettings
{
    bool debug{};
    const char *windowTitle{};
    int windowSize[2]{};
    WindowMode mode{};
    int monitor = 0;
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

struct OpenGL_Initialization_error : public std::exception
{
    const char *what() const noexcept override
    {
        return "Failed to initialize OpenGL context";
    }
};

class Engine
{
private:
    GLFWwindow *_window = nullptr;
public:
    Engine() = delete;
    Engine(const EngineSettings &settings);
    ~Engine() = default;

    GLFWwindow *getWindow() const;

};


#endif //QUACKENGINE_ENGINE_HPP
