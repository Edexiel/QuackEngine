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

void CharacterControllerSystem::CharacterMovement(Entity entity)
{
    auto &world = Engine::Instance().GetCurrentWorld();
    auto &rigidBody = world.GetComponent<RigidBody>(entity);
    auto &transform = world.GetComponent<Transform>(entity);
    auto &characterController = world.GetComponent<CharacterController>(entity);

//    float deltatime = (float)Engine::Instance().GetTimeManager().GetDeltaTime();

    float verticalAxis = characterController.forward + characterController.backward;
    float horizontalAxis = characterController.right + characterController.left;
    characterController.direction = ((Maths::Vector3f::Forward() * verticalAxis) + (Maths::Vector3f::Right() * horizontalAxis)).GetNormalized();

//    std::cout << "deltatime = " << deltatime << std::endl;

    rp3d::Transform t = rigidBody.rb->getTransform();
    rp3d::Vector3 v = t.getPosition();

    Maths::Vector3f pos{v.x, v.y, v.z};
    Maths::Quaternion rot;
    if(horizontalAxis != 0 || verticalAxis != 0)
    {
        rot = Maths::Quaternion::LookAt(Maths::Vector3f::Zero(), characterController.direction);
    }
    else
    {
        rp3d::Quaternion q = t.getOrientation();
        rot = Maths::Quaternion{q.w, q.x, q.y, q.z};
    }

    PhysicsSystem::SetTransform(entity, pos + characterController.direction * characterController.speed * (float)Engine::Instance().GetDeltaTime(), rot);
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