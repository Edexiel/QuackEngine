#ifndef QUACKENGINE_RIGIDBODY_HPP
#define QUACKENGINE_RIGIDBODY_HPP

#include "Scene/Component/ComponentBase.hpp"

#include <functional>
#include "Scene/Core/Types.hpp"
#include "Maths/Vector3.hpp"

namespace reactphysics3d
{
    class RigidBody;
}
enum class BodyType {STATIC, KINEMATIC, DYNAMIC};
enum class CollisionShapeType {SPHERE, CAPSULE, CONVEX_POLYHEDRON, CONCAVE_SHAPE};

class PhysicsEventManager;
class PhysicsSystem;

namespace Component
{
    class RigidBody : public ComponentBase
    {
    private:
        std::function<void(Entity, Entity)> _contactStart;
        std::function<void(Entity, Entity)> _contactStay;
        std::function<void(Entity, Entity)> _contactExit;

        std::function<void(Entity, Entity)> _overlapStart;
        std::function<void(Entity, Entity)> _overlapStay;
        std::function<void(Entity, Entity)> _overlapExit;

        BodyType _bodyType {BodyType::STATIC};
        CollisionShapeType _collisionShapeType;
        bool _isTrigger {false};
        bool _isGravityEnabled {true};
        float _mass{1};

        union ShapeParams
        {
            Maths::Vector3<float> halfExtends; // box collider
            struct { float radius; float height; }; // Sphere or Capsule
        };

        ShapeParams _shapeParams;

        friend ::PhysicsEventManager;
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
        Maths::Vector3<float> GetHalfExtends() const;
    };
}
#endif //QUACKENGINE_RIGIDBODY_HPP
