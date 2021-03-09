//
// Created by g.nisi on 3/9/21.
//

#include <glad/gl.h>
#include <cstdio>
#include "Engine.hpp"

int Engine::init(EngineSettings &settings)
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.gl.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.gl.minor);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, settings.gl.debug);
    glfwWindowHint(GLFW_OPENGL_PROFILE, settings.gl.profile);

    GLFWmonitor *monitor;

    switch (settings.window.mode)
    {
        case Window::Mode::WINDOWED:
        {
            monitor = NULL;
            break;
        }

        case Window::Mode::FULLSCREEN:
        {
            int count;
            GLFWmonitor **monitors = glfwGetMonitors(&count);

            if (settings.window.monitor < count)
            {
                monitor = monitors[settings.window.monitor];
                break;
            }

            monitor = glfwGetPrimaryMonitor();
            break;
        }

        case Window::Mode::WINDOWED_FULLSCREEN:
        {
            //todo: stuff
            //flemme, je verrais plus tard
            monitor = NULL;
            break;
        }
    }

    _window = glfwCreateWindow(settings.window.size[0],
                               settings.window.size[1],
                               settings.window.title, monitor, NULL);
    if (!_window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(_window);

    //todo: use interface
    int version = gladLoadGL(glfwGetProcAddress);

    if (version == 0)
    {
        printf("Failed to initialize OpenGL context");
        glfwTerminate();
        return -1;
    }

    printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION = %s\n", glGetString(GL_VERSION));

    _init = true;
}

bool Engine::isInit() const
{
    return _init;
}

GLFWwindow *Engine::getWindow() const
{
    return _window;
}
