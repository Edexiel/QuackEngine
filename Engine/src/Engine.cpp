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
 */
Engine::Engine(const EngineSettings& settings)
{

    if (!glfwInit())
        throw GLFW_Initialization_error();


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, settings.debug);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor;

    /**
     * Screen mode selection, can be
     * WINDOWED
     * FULLSCREEN
     * WINDOWED FULLSCREEN
     *
     * If there are multiple monitors, we can select it and execute the screen mode in that screen
     */
    switch (settings.mode)
    {
        case WindowMode::WINDOWED:
        {
            monitor = nullptr;
            break;
        }

        case WindowMode::FULLSCREEN:
        {
            int count;
            GLFWmonitor **monitors = glfwGetMonitors(&count);

            if (settings.monitor < count)
            {
                monitor = monitors[settings.monitor];
                break;
            }

            monitor = glfwGetPrimaryMonitor();
            break;
        }

        case WindowMode::WINDOWED_FULLSCREEN:
        {
            //todo: stuff
            //flemme, je verrais plus tard
            monitor = nullptr;
            break;
        }
    }

    _window = glfwCreateWindow(settings.windowSize[0],
                               settings.windowSize[1],
                               settings.windowTitle, monitor, nullptr);
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
        glfwTerminate();
        throw OpenGL_Initialization_error();
    }

    printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION = %s\n", glGetString(GL_VERSION));
}


/**
 * Return a GLFWwindow
 * @return
 */
GLFWwindow *Engine::getWindow() const
{
    return _window;
}
