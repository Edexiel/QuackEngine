#ifndef QUACKENGINE_RIGIDBODY_HPP
#define QUACKENGINE_RIGIDBODY_HPP

#include "reactphysics3d/reactphysics3d.h"

namespace Component
{
    struct RigidBody
    {
        rp3d::RigidBody *rb {nullptr};
    };
}
#endif //QUACKENGINE_RIGIDBODY_HPP
