//
// Created by g.nisi on 3/9/21.
//

#include <glad/gl.h>
#include <cstdio>
#include "Engine.hpp"



/**
 * Engine initialisation
 * We take the EngineSettings struct and -try to- initialize a screen context
 * @param settings
 * @return <0 init failed
 */
Engine::Engine(const EngineSettings& settings)
{

    if (!glfwInit())
        throw GLFW_Initialization_error();


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.gl.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.gl.minor);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, settings.gl.debug);
    glfwWindowHint(GLFW_OPENGL_PROFILE, settings.gl.profile);

    GLFWmonitor *monitor;

    /**
     * Screen mode selection, can be
     * WINDOWED
     * FULLSCREEN
     * WINDOWED FULLSCREEN
     *
     * If there are multiple monitors, we can select it and execute the screen mode in that screen
     */
    switch (settings.window.mode)
    {
        case Window::Mode::WINDOWED:
        {
            monitor = nullptr;
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
            monitor = nullptr;
            break;
        }
    }

    _window = glfwCreateWindow(settings.window.size[0],
                               settings.window.size[1],
                               settings.window.title, monitor, nullptr);
    if (!_window)
    {
        glfwTerminate();
        throw GLFW_Window_Initialization_error();
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

    return 0;
}

/**
 * Is the Engine initialized
 * @return
 */
bool Engine::isInit() const
{
    return _init;
}

/**
 * Return a GLFWwindow
 * @return
 */
GLFWwindow *Engine::getWindow() const
{
    return _window;
}

