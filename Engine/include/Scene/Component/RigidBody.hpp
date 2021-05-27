#ifndef QUACKENGINE_RIGIDBODY_HPP
#define QUACKENGINE_RIGIDBODY_HPP

#include <functional>
#include "Scene/Core/Types.hpp"
#include "Maths/Vector3.hpp"

namespace reactphysics3d
{
    class RigidBody;
    class CollisionBody;
}
enum class BodyType {STATIC, KINEMATIC, DYNAMIC};
enum class CollisionShapeType {SPHERE, CAPSULE, CONVEX_POLYHEDRON, CONCAVE_SHAPE, NONE = -1};

class PhysicsEventManager;
class PhysicsCollisionCallback;
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
        CollisionShapeType _collisionShapeType{CollisionShapeType::NONE};
        bool _isTrigger {false};
        bool _isGravityEnabled {true};
        float _mass{1};
        float _bounciness{0};

        union ShapeParams
        {
            Maths::Vector3<float> halfExtends; // box collider
            struct { float radius; float height; }; // Sphere or Capsule
        };

        ShapeParams _shapeParams;

        friend ::PhysicsEventManager;
        friend ::PhysicsCollisionCallback;
        friend ::PhysicsSystem;

    public:
        reactphysics3d::RigidBody *rb {nullptr};
        float GetMass() const;
        bool GetIsGravityEnabled() const;
        BodyType GetBodyType() const;
        bool GetIsTrigger() const;
        CollisionShapeType GetCollisionShapeType() const;
        float GetRadius() const;
        float GetHeight() const;
        float GetBounciness() const;
        Maths::Vector3<float> GetHalfExtends() const;
    };
}
#endif //QUACKENGINE_RIGIDBODY_HPP
