#ifndef QUACKENGINE_RIGIDBODY_HPP
#define QUACKENGINE_RIGIDBODY_HPP

#include <functional>
#include "Scene/Core/Types.hpp"

namespace reactphysics3d
{
    class RigidBody;
}


class PhysicsEventManager;
class PhysicsSystem;

namespace Component
{
    struct RigidBody
    {
        reactphysics3d::RigidBody *rb {nullptr};
    private:
        std::function<void(Entity, Entity)> _contactStart;
        std::function<void(Entity, Entity)> _contactStay;
        std::function<void(Entity, Entity)> _contactExit;

        std::function<void(Entity, Entity)> _overlapStart;
        std::function<void(Entity, Entity)> _overlapStay;
        std::function<void(Entity, Entity)> _overlapExit;

        friend ::PhysicsEventManager;
        friend ::PhysicsSystem;
    };
}
#endif //QUACKENGINE_RIGIDBODY_HPP
