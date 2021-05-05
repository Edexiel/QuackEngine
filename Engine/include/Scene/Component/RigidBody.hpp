#ifndef QUACKENGINE_RIGIDBODY_HPP
#define QUACKENGINE_RIGIDBODY_HPP

#include "reactphysics3d/reactphysics3d.h"
#include <functional>
#include "Scene/Core/Types.hpp"

class PhysicsEventManager;
class PhysicsSystem;

namespace Component
{
    struct RigidBody
    {
        rp3d::RigidBody *rb {nullptr};

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
