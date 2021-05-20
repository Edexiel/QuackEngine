#ifndef QUACKENGINE_ENGINE_HPP
#define QUACKENGINE_ENGINE_HPP

#include <vector>
#include <map>
#include <memory>
#include <string_view>

#include <Scene/Core/World.hpp>

#include "Resources/ResourcesManager.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Renderer/PostProcessManager.hpp"
#include "Audio/SoundManager.hpp"
#include <reactphysics3d/engine/PhysicsCommon.h>
#include "Time/TimeManager.hpp"


#include "Input/InputManager.hpp"
#include "Input/PlatformInput.hpp"

#include "Input/PlatformInput.hpp"
#include "Input/PlatformInputGLFW.hpp"


enum class WINDOW_MODE
{
    WINDOWED,
    FULLSCREEN,
    WINDOWED_FULLSCREEN,
};

enum class INPUT_MODE
{
    GLFW,
};

struct EngineSettings
{
    bool debug{};
    std::string windowTitle{};
    int windowSize[2]{};
    WINDOW_MODE mode{};
    int monitor = 0;
    INPUT_MODE inputMode;
};

class Engine
{
private:
    class GLFWwindow *_window = nullptr;

    std::unique_ptr<Input::PlatformInput> _platformInput;

    Renderer::RendererInterface _rendererInterface; //init after world loading
    Resources::ResourcesManager _resourcesManager;
    Audio::SoundManager _soundManager;
    PhysicsEventManager _physicsEventManager;
    reactphysics3d::PhysicsCommon _physicsManager;
    Input::InputManager _inputManager;
    Time::TimeManager _timeManager;
    Renderer::PostProcessManager _postProcessManager;

    uint_fast16_t _currentWorld = 0;
    std::map<std::string_view , uint_fast16_t> _worldLut;
    std::vector<World> _worlds;

public:
    static Engine &Instance();
    static void SetInstance(Engine &engine);

    explicit Engine(const EngineSettings &settings);
    ~Engine();

    GLFWwindow *GetWindow();
    void SetWindowTitle(const std::string &title);
    void SetWindowSize(int width, int height);
    bool WindowShouldClose();
    void TestWindowShouldClose();
    World &GetCurrentWorld();
    void SwapBuffers();

    World &CreateWorld(std::string_view name);
    void LoadWorld(const std::string &name);
    void UnloadWorld(const std::string &name);
    void RemoveWorld(const std::string &name);

    Input::InputManager &GetInputManager();
    Renderer::RendererInterface &GetRendererInterface();
    Resources::ResourcesManager &GetResourcesManager();
    Audio::SoundManager &GetSoundManager();
    PhysicsEventManager &GetPhysicsEventManager();
    reactphysics3d::PhysicsCommon &GetPhysicsManager();
    Time::TimeManager &GetTimeManager();
    Renderer::PostProcessManager &GetPostProcessManager();
};

#endif //QUACKENGINE_ENGINE_HPP
