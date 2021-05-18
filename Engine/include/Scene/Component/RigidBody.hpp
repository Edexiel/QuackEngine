#ifndef QUACKENGINE_RIGIDBODY_HPP
#define QUACKENGINE_RIGIDBODY_HPP

#include <functional>
#include "Scene/Core/Types.hpp"

namespace reactphysics3d
{
    class RigidBody;
}
enum class BodyType {STATIC, KINEMATIC, DYNAMIC};

class PhysicsEventManager;
class PhysicsSystem;

namespace Component
{
    struct RigidBody
    {
    private:
        std::function<void(Entity, Entity)> _contactStart;
        std::function<void(Entity, Entity)> _contactStay;
        std::function<void(Entity, Entity)> _contactExit;

        std::function<void(Entity, Entity)> _overlapStart;
        std::function<void(Entity, Entity)> _overlapStay;
        std::function<void(Entity, Entity)> _overlapExit;

        BodyType _bodyType {BodyType::STATIC};
        float _mass{1};

        friend ::PhysicsEventManager;
        friend ::PhysicsSystem;

    public:
        reactphysics3d::RigidBody *rb {nullptr};
        float GetMass() const
        {
            return _mass;
        }
        BodyType GetBodyType() const
        {
            return _bodyType;
        }
    };
}
#endif //QUACKENGINE_RIGIDBODY_HPP
