#include "Engine.hpp"

#include "GLFW/glfw3.h"
#include <algorithm>

#include <Renderer/RendererInterface.hpp>
#include <Resources/ResourcesManager.hpp>
#include "Audio/SoundManager.hpp"
#include "Time/TimePlatformGLFW.hpp"

#include "Renderer/RendererPlatform.hpp"

#include "Debug/Assertion.hpp"


inline Engine *instance = nullptr;

Engine &Engine::Instance()
{
    return *instance;
}

void Engine::SetInstance(Engine &engine)
{
    instance = &engine;
}

Engine::~Engine()
{
    glfwTerminate();
}

Engine::Engine(const EngineSettings &settings)
{
    Assert_Fatal_Error(instance != nullptr, "There should be only one Engine");
    Assert_Fatal_Error(!glfwInit(), "GLFW was not correctly initialized, aborting");

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
        case WINDOW_MODE::WINDOWED:
        {
            monitor = nullptr;
            break;
        }

        case WINDOW_MODE::FULLSCREEN:
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

        case WINDOW_MODE::WINDOWED_FULLSCREEN:
        {
            //todo: stuff
            //flemme, je verrais plus tard
            monitor = nullptr;
            break;
        }
    }

    _window = glfwCreateWindow(settings.windowSize[0],
                               settings.windowSize[1],
                               settings.windowTitle.c_str(), monitor, nullptr);
    if (!_window)
    {
        glfwTerminate();
        Assert_Fatal_Error(true, "GLFW's window was not correctly initialized, aborting");
    }

    glfwMakeContextCurrent(_window);

    int version = Renderer::RendererPlatform::LoadGl();

    if (version == 0)
    {
        glfwTerminate();
        Assert_Fatal_Error(true, "Failed to initialize OpenGL context");
    }


    switch (settings.inputMode)
    {
        case INPUT_MODE::GLFW:
            break;
    }
    _platformInput = std::make_unique<Input::PlatformInputGLFW>(_window);
    //Assert_Fatal_Error(_platformInput, "Platform input not declared");
    _inputManager.Init(_platformInput.get());
    _timeManager.Init(new Time::TimePlatformGLFW(_window));
    _postProcessManager.Init();
}

GLFWwindow *Engine::GetWindow()
{
    return _window;
}

void Engine::SetWindowTitle(const std::string &title)
{
    glfwSetWindowTitle(_window, title.c_str());
}

void Engine::SetWindowSize(int width, int height)
{
    glfwSetWindowSize(_window, width, height);

}

bool Engine::WindowShouldClose()
{
    return glfwWindowShouldClose(_window);
}

Renderer::RendererInterface &Engine::GetRendererInterface()
{
    return _rendererInterface;
}

Resources::ResourcesManager &Engine::GetResourcesManager()
{
    return _resourcesManager;
}

Audio::SoundManager &Engine::GetSoundManager()
{
    return _soundManager;
}

reactphysics3d::PhysicsCommon &Engine::GetPhysicsManager()
{
    return _physicsManager;
}

Input::InputManager &Engine::GetInputManager()
{
    return _inputManager;
}

World &Engine::GetCurrentWorld()
{
    return _worlds[_currentWorld];
}

World &Engine::CreateWorld(std::string_view name)
{
    _worldLut.insert({name, (uint_fast16_t) _worlds.size()});
    return _worlds.emplace_back(name);
}

void Engine::LoadWorld(const std::string &name)
{

}

void Engine::UnloadWorld(const std::string &name)
{
    _worlds[_worldLut[name]].Clear();
}

void Engine::RemoveWorld(const std::string &name)
{
    uint_fast16_t index = _worldLut[name];
    std::string_view back_name = _worlds.back().GetName();
    std::swap(_worlds[index], _worlds.back());
    _worlds.pop_back();
    _worldLut[back_name] = index;
}

void Engine::TestWindowShouldClose()
{
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(_window, 1);
    }
}

void Engine::SwapBuffers()
{
    glfwSwapBuffers(_window);
}

PhysicsEventManager &Engine::GetPhysicsEventManager()
{
    return _physicsEventManager;
}

Time::TimeManager &Engine::GetTimeManager()
{
    return _timeManager;
}

Renderer::PostProcessManager &Engine::GetPostProcessManager()
{
    return _postProcessManager;
}


