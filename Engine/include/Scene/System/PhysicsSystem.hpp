#ifndef QUACKENGINE_PHYSICSSYSTEM_HPP
#define QUACKENGINE_PHYSICSSYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Scene/Core/Types.hpp"

#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"

#include <utility>

namespace reactphysics3d
{
    class PhysicsWorld;

    class PhysicsCommon;
}

enum class BodyType {STATIC, KINEMATIC, DYNAMIC};


namespace Component
{
    struct RigidBody;
}

class PhysicsSystem : public System
{
public:

    void Init();
    void SetRigidBody(Entity id);

    void FixedUpdate(float fixedDeltaTime);

    void SetType(Entity id, const BodyType& type);

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

#endif //QUACKENGINE_PHYSICSSYSTEM_HPP
