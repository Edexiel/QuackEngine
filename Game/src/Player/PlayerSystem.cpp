#include "Player/PlayerSystem.hpp"
#include "Engine.hpp"


#include "Scene/Core/World.hpp"
#include "Scene/Component/CharacterController.hpp"
#include "Player/PlayerComponent.hpp"

PlayerSystem::PlayerSystem():engine{Engine::Instance()}
{
    Input::InputManager& inputManager = engine.GetInputManager();

    inputManager.BindEvent("Up", Input::Key::KEY_UP);
    inputManager.RegisterEvent("Up", Input::Action::PRESS, this, &PlayerSystem::Up);

    inputManager.BindEvent("Down", Input::Key::KEY_DOWN);
    inputManager.RegisterEvent("Down", Input::Action::PRESS, this, &PlayerSystem::Down);

    inputManager.BindEvent("Right", Input::Key::KEY_RIGHT);
    inputManager.RegisterEvent("Right", Input::Action::PRESS, this, &PlayerSystem::Right);

    inputManager.BindEvent("Left", Input::Key::KEY_LEFT);
    inputManager.RegisterEvent("Left", Input::Action::PRESS, this, &PlayerSystem::Left);

    inputManager.BindEventAxis("Move up", Input::Key::KEY_W, 1.f);
    inputManager.RegisterEventAxis("Move up", this, &PlayerSystem::MoveForward);
    inputManager.BindEventAxis("Move down", Input::Key::KEY_S, -1.f);
    inputManager.RegisterEventAxis("Move down", this, &PlayerSystem::MoveBackward);
    inputManager.BindEventAxis("Move left", Input::Key::KEY_A, -1.f);
    inputManager.RegisterEventAxis("Move left", this, &PlayerSystem::MoveLeft);
    inputManager.BindEventAxis("Move right", Input::Key::KEY_D, 1.f);
    inputManager.RegisterEventAxis("Move right", this, &PlayerSystem::MoveRight);

}

void PlayerSystem::Update()
{
    if (!_running)
        return;

    auto &world = engine.GetCurrentWorld();

    for(Entity entity : _entities)
    {
        if(!world.HasComponent<Component::CharacterController>(entity))
            return;
        auto &characterController = world.GetComponent<Component::CharacterController>(entity);
        if (characterController.forward == 0.0f &&
                characterController.backward == 0.0f &&
                characterController.right == 0.0f &&
                characterController.left == 0.0f)
        {
            StopRunning();
        }

    }
}


void PlayerSystem::Up()
{
    for (Entity entity : _entities)
    {
        engine.GetCurrentWorld().GetComponent<PlayerComponent>(entity).GetPlayerSound().PlayUpSound();
    }
}

void PlayerSystem::Down()
{
    for (Entity entity : _entities)
    {
        engine.GetCurrentWorld().GetComponent<PlayerComponent>(entity).GetPlayerSound().PlayDownSound();
    }
}

void PlayerSystem::Right()
{
    for (Entity entity : _entities)
    {
        engine.GetCurrentWorld().GetComponent<PlayerComponent>(entity).GetPlayerSound().PlayRightSound();
    }
}

void PlayerSystem::Left()
{
    for (Entity entity : _entities)
    {
        engine.GetCurrentWorld().GetComponent<PlayerComponent>(entity).GetPlayerSound().PlayLeftSound();
    }
}

void PlayerSystem::MoveForward(float verticalAxis)
{
    StartRunning();
    auto &world = engine.GetCurrentWorld();

    for(Entity entity : _entities)
    {
        if(!world.HasComponent<Component::CharacterController>(entity))
            return;
        auto &characterController = world.GetComponent<Component::CharacterController>(entity);
        characterController.forward = verticalAxis;
    }
}

void PlayerSystem::MoveRight(float horizontalAxis)
{
    StartRunning();
    auto &world = engine.GetCurrentWorld();
    for(Entity entity : _entities)
    {
        if(!world.HasComponent<Component::CharacterController>(entity))
            return;
        auto &characterController = world.GetComponent<Component::CharacterController>(entity);
        characterController.right = horizontalAxis;
    }
}

void PlayerSystem::MoveBackward(float verticalAxis)
{
    StartRunning();
    auto &world = engine.GetCurrentWorld();
    for(Entity entity : _entities)
    {
        if(!world.HasComponent<Component::CharacterController>(entity))
            return;
        auto &characterController = world.GetComponent<Component::CharacterController>(entity);
        characterController.backward = verticalAxis;
    }
}

void PlayerSystem::MoveLeft(float horizontalAxis)
{
    StartRunning();
    auto &world = engine.GetCurrentWorld();
    for(Entity entity : _entities)
    {
        if(!world.HasComponent<Component::CharacterController>(entity))
            return;
        auto &characterController = world.GetComponent<Component::CharacterController>(entity);
        characterController.left = horizontalAxis;
    }
}

void PlayerSystem::StartRunning()
{
    if (_running)
        return;
    auto &world = engine.GetCurrentWorld();
    for(Entity entity : _entities)
    {
        auto &player = world.GetComponent<PlayerComponent>(entity);
        player.RunAnimation(true);
    }
    _running = true;
}

void PlayerSystem::StopRunning()
{
    if (!_running)
        return;
    auto &world = engine.GetCurrentWorld();
    for(Entity entity : _entities)
    {
        auto &player = world.GetComponent<PlayerComponent>(entity);
        player.RunAnimation(false);
    }
    _running = false;
}