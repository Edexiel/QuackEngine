#ifndef QUACKENGINE_PHYSICSSYSTEM_HPP
#define QUACKENGINE_PHYSICSSYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Scene/Core/Types.hpp"

#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"
#include "Scene/Component/RigidBody.hpp"

#include <utility>
#include <functional>

namespace reactphysics3d
{
    class PhysicsWorld;

    class PhysicsCommon;
}


enum class PhysicsEventType
{
    OverlapStart,
    OverlapStay,
    OverlapExit,

    ContactStart,
    ContactStay,
    ContactExit,
};
namespace Component
{
    struct RigidBody;
}

class PhysicsSystem : public System
{
public:

    void Init();
    static void SetRigidBody(Entity id);

    void FixedUpdate(float fixedDeltaTime);

    static void SetType(Entity id, const BodyType& type);
    static void SetMass(Entity id, float mass);
    static void SetIsTrigger(Entity id, bool isTrigger);
    static void SetVelocity(Entity id, const Maths::Vector3f &velocity);
    template<typename C, typename F>
    static void SetPhysicEvent(Entity id, PhysicsEventType type, C *classObject, F && function);

    static void AddBoxCollider(Entity id, const Maths::Vector3f &halfExtend, const Maths::Vector3f &position = {0, 0, 0},
                        const Maths::Quaternion &rotation = {1, 0, 0, 0});

    static void AddSphereCollider(Entity id, float radius, const Maths::Vector3f &position = {0, 0, 0},
                           const Maths::Quaternion &rotation = {1, 0, 0, 0});

    static void AddCapsuleCollider(Entity id, float radius,
                            float height,
                            const Maths::Vector3f &position = {0, 0, 0},
                            const Maths::Quaternion &rotation = {1, 0, 0, 0});

    static void ResizeBoxCollider(Entity id, const Maths::Vector3f &halfExtend);
    static void ResizeSphereCollider(Entity id, float radius);
    static void ResizeCapsuleCollider(Entity id, float radius, float height);

    static void SetIsGravityEnable(Entity id, bool isGravityEnable);

    //todo: create function to change world settings.
};

template<typename C, typename F>
void PhysicsSystem::SetPhysicEvent(Entity id, PhysicsEventType type, C *classObject, F &&function)
{
    World &world = Engine::Instance().GetCurrentWorld();
    if(!world.HasComponent<Component::RigidBody>(id))
        return;

    auto &rb = world.GetComponent<Component::RigidBody>(id);

    switch(type)
    {
        case PhysicsEventType::OverlapStart :
        {
            rb._overlapStart = std::bind(function, classObject, std::placeholders::_1, std::placeholders::_2);
            break;
        }
        case PhysicsEventType::OverlapStay :
        {
            rb._overlapStay = std::bind(function, classObject, std::placeholders::_1, std::placeholders::_2);
            break;
        }
        case PhysicsEventType::OverlapExit :
        {
            rb._overlapExit = std::bind(function, classObject, std::placeholders::_1, std::placeholders::_2);
            break;
        }
        case PhysicsEventType::ContactStart :
        {
            rb._contactStart = std::bind(function, classObject, std::placeholders::_1, std::placeholders::_2);
            break;
        }
        case PhysicsEventType::ContactStay :
        {
            rb._contactStay = std::bind(function, classObject, std::placeholders::_1, std::placeholders::_2);
            break;
        }
        case PhysicsEventType::ContactExit :
        {
            rb._contactExit = std::bind(function, classObject, std::placeholders::_1, std::placeholders::_2);
            break;
        }
        default:
            break;
    }
}
#endif //QUACKENGINE_PHYSICSSYSTEM_HPP
