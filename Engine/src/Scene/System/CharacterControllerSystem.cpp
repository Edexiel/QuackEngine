#include "Scene/System/CharacterControllerSystem.hpp"
#include "Scene/System/PhysicsSystem.hpp"

#include "reactphysics3d/reactphysics3d.h"
#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Input/InputManager.hpp"
#include "Scene/Component/RigidBody.hpp"
#include "Scene/Component/CharacterController.hpp"

using namespace Component;

void CharacterControllerSystem::Update()
{
    auto &world = Engine::Instance().GetCurrentWorld();
    auto &collisionCallback = Engine::Instance().GetPhysicsCollisionCallback();
    auto physicWorld = world.GetPhysicsWorld();
    for(Entity entity : _entities)
    {
        CharacterMovement(entity);
        auto &rigidBody = world.GetComponent<RigidBody>(entity);
        physicWorld->testCollision(rigidBody.rb, collisionCallback);
    }
}

void CharacterControllerSystem::Init()
{
    auto &inputManager = Engine::Instance().GetInputManager();

    inputManager.BindEventAxis("Move up", Input::Key::KEY_W, 1.f);
    inputManager.RegisterEventAxis("Move up", this, &CharacterControllerSystem::MoveForward);

    inputManager.BindEventAxis("Move down", Input::Key::KEY_S, -1.f);
    inputManager.RegisterEventAxis("Move down", this, &CharacterControllerSystem::MoveBackward);

    inputManager.BindEventAxis("Move left", Input::Key::KEY_A, -1.f);
    inputManager.RegisterEventAxis("Move left", this, &CharacterControllerSystem::MoveLeft);

    inputManager.BindEventAxis("Move right", Input::Key::KEY_D, 1.f);
    inputManager.RegisterEventAxis("Move right", this, &CharacterControllerSystem::MoveRight);
}

void CharacterControllerSystem::MoveForward(float verticalAxis)
{
    auto &world = Engine::Instance().GetCurrentWorld();

    for(Entity entity : _entities)
    {
        auto &characterController = world.GetComponent<CharacterController>(entity);
        characterController.forward = verticalAxis;
    }
}

void CharacterControllerSystem::MoveRight(float horizontalAxis)
{
    auto &world = Engine::Instance().GetCurrentWorld();
    for(Entity entity : _entities)
    {
        auto &characterController = world.GetComponent<CharacterController>(entity);
        characterController.right = horizontalAxis;
    }
}

void CharacterControllerSystem::MoveBackward(float verticalAxis)
{
    auto &world = Engine::Instance().GetCurrentWorld();
    for(Entity entity : _entities)
    {
        auto &characterController = world.GetComponent<CharacterController>(entity);
        characterController.backward = verticalAxis;
    }
}

void CharacterControllerSystem::MoveLeft(float horizontalAxis)
{
    auto &world = Engine::Instance().GetCurrentWorld();
    for(Entity entity : _entities)
    {
        auto &characterController = world.GetComponent<CharacterController>(entity);
        characterController.left = horizontalAxis;
    }
}

void CharacterControllerSystem::CharacterMovement(Entity entity)
{
    auto &world = Engine::Instance().GetCurrentWorld();
    auto &rigidBody = world.GetComponent<RigidBody>(entity);
    auto &transform = world.GetComponent<Transform>(entity);
    auto &characterController = world.GetComponent<CharacterController>(entity);

    float deltatime = (float)Engine::Instance().GetTimeManager().GetDeltaTime();

    float verticalAxis = characterController.forward + characterController.backward;
    float horizontalAxis = characterController.right + characterController.left;
    characterController.direction = ((Maths::Vector3f::Forward() * verticalAxis) + (Maths::Vector3f::Right() * horizontalAxis)).GetNormalized();

//    std::cout << "deltatime = " << deltatime << std::endl;

    rp3d::Transform t = rigidBody.rb->getTransform();
    rp3d::Vector3 v = t.getPosition();
    rp3d::Quaternion q = t.getOrientation();

    Maths::Vector3f pos{v.x, v.y, v.z};
    Maths::Quaternion rot{q.w, q.x, q.y, q.z};

    PhysicsSystem::SetTransform(entity, pos + characterController.direction * characterController.speed * 0.06f, rot);
}

void CharacterControllerSystem::CollideWithWall(Entity player,const Maths::Vector3f &normal, float depth)
{
    auto &world = Engine::Instance().GetCurrentWorld();
    auto &rigidBody = world.GetComponent<RigidBody>(player);

    rp3d::Vector3 v = rigidBody.rb->getTransform().getPosition();
    rp3d::Quaternion q = rigidBody.rb->getTransform().getOrientation();

    Maths::Vector3f pos{v.x, v.y, v.z};
    Maths::Quaternion rot{q.w, q.x, q.y, q.z};

    PhysicsSystem::SetTransform(player, pos - normal * (depth), rot);
}