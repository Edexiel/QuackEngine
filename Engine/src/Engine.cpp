#include <vector>
#include <algorithm>
#include "Engine.hpp"

#include "Scene/Core/World.hpp"
#include "GLFW/glfw3.h"

#include <Renderer/RendererInterface.hpp>
#include <Resources/ResourcesManager.hpp>
#include "Audio/SoundManager.hpp"
#include "Time/TimePlatformGLFW.hpp"

#include "Renderer/RendererPlatform.hpp"

#include "Debug/Assertion.hpp"
#include "Debug/Log.hpp"

//Serialization
#include <cereal/archives/json.hpp>

namespace fs = std::filesystem;

inline Engine *instance = nullptr;

Engine &Engine::Instance() noexcept
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

Engine::Engine(const EngineSettings &settings) noexcept
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
            _window = glfwCreateWindow(settings.windowSize[0],
                                       settings.windowSize[1],
                                       settings.windowTitle.c_str(), monitor, nullptr);
            break;
        }

        case WINDOW_MODE::FULLSCREEN:
        {
            int count;
            GLFWmonitor **monitors = glfwGetMonitors(&count);

            if (settings.monitor < count)
            {
                _window = glfwCreateWindow(settings.windowSize[0],
                                           settings.windowSize[1],
                                           settings.windowTitle.c_str(), nullptr, nullptr);
                monitor = monitors[settings.monitor];
                break;
            }

            monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            _window = glfwCreateWindow(mode->width, mode->height,
                                       settings.windowTitle.c_str(), monitor, nullptr);
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
    glfwSwapInterval(0);

    _platformInput = std::make_unique<Input::PlatformInputGLFW>(_window);
    _inputManager.Init(_platformInput.get());
    _timeManager.Init(new Time::TimePlatformGLFW(_window));
    _postProcessManager.Init();
    _soundManager.Init();
    _resourcesManager.Init();

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

Maths::Vector2i Engine::GetWindowSize()
{
    Maths::Vector2i size{};
    glfwGetWindowSize(_window, &size.x, &size.y);
    return size;
}

bool Engine::WindowShouldClose()
{
    return glfwWindowShouldClose(_window);
}

void Engine::CloseWindows()
{
    glfwSetWindowShouldClose(_window, 1);

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


World &Engine::CreateWorld(std::string name)
{
    _worldLut.insert({name, (uint_fast16_t) _worlds.size()});
    return _worlds.emplace_back(name);
}

void Engine::SaveWorld(const std::string &worldName)
{
    World &oldWorld = GetCurrentWorld();
    SetCurrentWorld(worldName);

    fs::path path{"./Asset"};

    if (_worldLut.find(worldName) == _worldLut.end())
    {
        Log_Error("Trying to save a world that does not exists: {}", path.string());
        return;
    }
//Scene
    {
        Log_Info("Saving world : {}", worldName);
        std::filesystem::path worldPath = path;
        worldPath.append("Scenes");
        worldPath.append(worldName).replace_extension(".qck");
        std::ofstream os(worldPath);

        cereal::JSONOutputArchive oarchive(os);

        oarchive(cereal::make_nvp("world", _worlds.at(_worldLut.at(worldName))));
        Log_Info("World has been saved as: {}", worldPath.string());
    }
//Materials
    {
        std::filesystem::path materialPath = path;
        Log_Info("Saving materials");
        materialPath.append("Materials");
        if (!exists(materialPath))
        {
            std::filesystem::create_directory(materialPath);
        }

        std::vector<std::string> materials = _resourcesManager.GetMaterialNameList();
        for (const auto &name : materials)
        {
            std::filesystem::path tempPath = materialPath;
            tempPath.append(name).replace_extension(".qmt");
            std::ofstream os(tempPath);

            cereal::JSONOutputArchive oarchive(os);

            oarchive(cereal::make_nvp(name, *_resourcesManager.LoadMaterial(name)));
        }
        Log_Info("Materials have been saved", path.string());
    }
    SetCurrentWorld(oldWorld.GetName());

}

void Engine::FillTexture(Renderer::Texture &T)
{
    if (!T.GetPath().empty())
    {
        T = _resourcesManager.LoadTexture(T.GetPath());
    }
}

void Engine::LoadWorld(World &world)
{
    World &oldWorld = GetCurrentWorld();
    SetCurrentWorld(world.GetName());
    _worlds.at(_currentWorld).Register();

    const fs::path path{"./Asset"};
    if (!exists(path))
        Log_Error("Path does not exists: {}", path.string());


    //Materials
    {
        std::filesystem::path materialPath = path;
        materialPath.append("Materials");
        if (exists(materialPath))
        {
            for (const auto &p : std::filesystem::recursive_directory_iterator(materialPath))
            {
                if (!p.is_directory())
                {
                    std::string extension = p.path().extension().string();
                    if (extension == ".qmt")
                    {
                        Renderer::Material material;

                        std::ifstream is(p.path());
                        cereal::JSONInputArchive iarchive(is);

                        iarchive(material);

                        FillTexture(material.colorTexture);
                        FillTexture(material.diffuseTexture);
                        FillTexture(material.specularTexture);
                        FillTexture(material.normalMap);

                        _resourcesManager.GenerateMaterial(p.path().filename().replace_extension("").string(),
                                                           material);
                    }
                }

            }
        }
    }
    //World
    {
        std::filesystem::path worldPath = path;
        worldPath.append("Scenes");
        worldPath.append(world.GetName()).replace_extension(".qck");

        Log_Info("Loading world: {}", worldPath.string());

        if (!exists(worldPath))
        {
            SaveWorld(world.GetName());
        }

        std::ifstream is(worldPath);
        cereal::JSONInputArchive iarchive(is);

        iarchive(world);
    }
    world.InitSystems();
    SetCurrentWorld(oldWorld.GetName());
}

void Engine::RemoveWorld(const std::string &name)
{
    Log_Info("Removing world {}", name);

    auto it = _worldLut.find(name);
    if (it == _worldLut.end())
    {
        Log_Error("Could not find world \"{}\" to delete", name);
        return;
    }

    uint_fast16_t index = _worldLut.at(name);
    std::string back_name = _worlds.back().GetName();
    std::swap(_worlds[index], _worlds.back());
    _worlds.pop_back();
    _worldLut[back_name] = index;
    _worldLut.erase(name);

    std::filesystem::path worldPath("./Asset/Scenes");
    worldPath.append(name).replace_extension("qck");

    if (std::filesystem::remove(worldPath))
    {
        Log_Info("World {} removed", name);
    }

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

bool Engine::IsGamePlaying() const
{
    return _gamePlaying;
}

void Engine::SetGamePlaying(bool gamePlaying)
{
    _gamePlaying = gamePlaying;
}

void Engine::UpdateTime()
{
    _timeManager.Update();

    _timeAcc += _timeManager.GetDeltaTime();
    _frames++;

    if (_timeAcc >= 1.0f)
    {
        _fps = std::roundf(1.f / ((float)_timeAcc / (float)_frames));
        _frames = 0;
        _timeAcc = 0.;
    }

}

PhysicsCollisionCallback &Engine::GetPhysicsCollisionCallback()
{
    return _physicsCollisionCallback;
}

float Engine::GetFps() const
{
    return _fps;
}

double Engine::GetDeltaTime()
{
    return _timeManager.GetDeltaTime();
}

void Engine::ClearWorld(const std::string &worldName)
{
    _worlds[_worldLut[worldName]].Clear();
}

std::vector<std::string> Engine::GetWorldList() const
{
    std::vector<std::string> res{};
    for (const auto &item : _worldLut)
        res.push_back(item.first);

    return res;
}

void Engine::SetCurrentWorld(const std::string &name)
{
    auto it = _worldLut.find(name);
    if (it == _worldLut.end())
        return;
    _currentWorld = it->second;
    _worlds.at(_currentWorld).InitSettings();
}

