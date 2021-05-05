#ifndef QUACKENGINE_RIGIDBODY_HPP
#define QUACKENGINE_RIGIDBODY_HPP

namespace reactphysics3d
{
    class RigidBody;
}

namespace Component
{
    struct RigidBody
    {
        reactphysics3d::RigidBody *rb {nullptr};
    };
}
#endif //QUACKENGINE_RIGIDBODY_HPP
