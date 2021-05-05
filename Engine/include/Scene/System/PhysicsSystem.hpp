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

enum class BodyType {STATIC, KINEMATIC, DYNAMIC};
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
private:
    World* _world;
public:

    void Init();
    void SetRigidBody(Entity id);

    void FixedUpdate(float fixedDeltaTime);

    void SetType(Entity id, const BodyType& type);

    void SetIsTrigger(Entity id, bool isTrigger);
    template<typename C, typename F>
    void SetPhysicEvent(Entity id, PhysicsEventType type, C *classObject, F && function);

    void AddBoxCollider(Entity id, const Maths::Vector3f &halfExtend, const Maths::Vector3f &position = {0, 0, 0},
                        const Maths::Quaternion &rotation = {1, 0, 0, 0});

    void AddSphereCollider(Entity id, float radius, const Maths::Vector3f &position = {0, 0, 0},
                           const Maths::Quaternion &rotation = {1, 0, 0, 0});

    void AddCapsuleCollider(Entity id, float radius,
                            float height,
                            const Maths::Vector3f &position = {0, 0, 0},
                            const Maths::Quaternion &rotation = {1, 0, 0, 0});


    //todo: create function to change world settings.
};

template<typename C, typename F>
void PhysicsSystem::SetPhysicEvent(Entity id, PhysicsEventType type, C *classObject, F &&function)
{
    World &world = Engine::Instance().GetCurrentWorld();
    if(!world.HasComponent<Component::RigidBody>(id))
        return;

    Component::RigidBody &rb = world.GetComponent<Component::RigidBody>(id);

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
