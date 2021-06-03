#include "Player/PlayerSystem.hpp"

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
        engine.GetCurrentWorld().GetComponent<PlayerComponent>(entity).GetPlayerSound().PlayUpSound();
    }
}

void PlayerSystem::Right()
{
    for (Entity entity : _entities)
    {
        engine.GetCurrentWorld().GetComponent<PlayerComponent>(entity).GetPlayerSound().PlayUpSound();
    }
}

void PlayerSystem::Left()
{
    for (Entity entity : _entities)
    {
        engine.GetCurrentWorld().GetComponent<PlayerComponent>(entity).GetPlayerSound().PlayUpSound();
    }
}

void PlayerSystem::MoveForward(float verticalAxis)
{
    auto &world = engine.GetCurrentWorld();

    for(Entity entity : _entities)
    {
        auto &characterController = world.GetComponent<Component::CharacterController>(entity);
        characterController.forward = verticalAxis;
    }
}

void PlayerSystem::MoveRight(float horizontalAxis)
{
    auto &world = engine.GetCurrentWorld();
    for(Entity entity : _entities)
    {
        auto &characterController = world.GetComponent<Component::CharacterController>(entity);
        characterController.right = horizontalAxis;
    }
}

void PlayerSystem::MoveBackward(float verticalAxis)
{
    auto &world = engine.GetCurrentWorld();
    for(Entity entity : _entities)
    {
        auto &characterController = world.GetComponent<Component::CharacterController>(entity);
        characterController.backward = verticalAxis;
    }
}

void PlayerSystem::MoveLeft(float horizontalAxis)
{
    auto &world = engine.GetCurrentWorld();
    for(Entity entity : _entities)
    {
        auto &characterController = world.GetComponent<Component::CharacterController>(entity);
        characterController.left = horizontalAxis;
    }
}