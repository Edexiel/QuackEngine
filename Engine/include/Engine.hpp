#ifndef QUACKENGINE_ENGINE_HPP
#define QUACKENGINE_ENGINE_HPP

#include <vector>
#include <map>
#include <memory>

#include <Scene/Core/World.hpp>

#include "Resources/ResourcesManager.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Audio/SoundManager.hpp"
#include <reactphysics3d/reactphysics3d.h>
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
    Engine() noexcept = default;
    static Engine _instance;

    class GLFWwindow *_window = nullptr;

    std::unique_ptr<Input::PlatformInput> _platformInput;

    Renderer::RendererInterface _rendererInterface; //init after world loading
    Resources::ResourcesManager _resourcesManager;
    Audio::SoundManager _soundManager;
    rp3d::PhysicsCommon _physicsManager;
    Input::InputManager _inputManager;

    uint_fast16_t _currentWorld = 0;
    std::map<std::string, uint_fast16_t> _worldLut;
    std::vector<World> _worlds;

public:
    static Engine &Instance();
    ~Engine();

    void InitWindow(const EngineSettings &settings);
    GLFWwindow *GetWindow();
    void SetWindowTitle(const std::string &title);
    void SetWindowSize(int width, int height);
    bool WindowShouldClose();
    void testWindowShouldClose();
    World &GetCurrentWorld();
    void SwapBuffers();


    World& CreateWorld(std::string name);
    void LoadWorld(const std::string& name);
    void UnloadWorld(const std::string& name);
    void RemoveWorld(const std::string& name);

    Input::InputManager &GetInputManager() ;
    Renderer::RendererInterface &GetRendererInterface();
    Resources::ResourcesManager &GetResourcesManager();
    Audio::SoundManager &GetSoundManager();
    rp3d::PhysicsCommon &GetPhysicsManager();
};

inline Engine Engine::_instance = Engine();

inline Engine &Engine::Instance()
{
    return _instance;
}


#endif //QUACKENGINE_ENGINE_HPP
