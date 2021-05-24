#ifndef QUACKENGINE_RIGIDBODY_HPP
#define QUACKENGINE_RIGIDBODY_HPP

#include <functional>
#include "Scene/Core/Types.hpp"
#include "Maths/Vector3.hpp"
#include "cereal/access.hpp"


namespace reactphysics3d
{
    class RigidBody;
}
enum class BodyType
{
    STATIC, KINEMATIC, DYNAMIC
};
enum class CollisionShapeType
{
    SPHERE, CAPSULE, CONVEX_POLYHEDRON, CONCAVE_SHAPE
};

class PhysicsEventManager;

class PhysicsSystem;

namespace Component
{
    struct RigidBody
    {
    private:
        union ShapeParams
        {
            Maths::Vector3<float> halfExtends; // box collider
            struct
            {
                float radius;
                float height;
            }; // Sphere or Capsule
        };

        std::function<void(Entity, Entity)> _contactStart;
        std::function<void(Entity, Entity)> _contactStay;
        std::function<void(Entity, Entity)> _contactExit;

        std::function<void(Entity, Entity)> _overlapStart;
        std::function<void(Entity, Entity)> _overlapStay;
        std::function<void(Entity, Entity)> _overlapExit;

        BodyType _bodyType{BodyType::STATIC};
        CollisionShapeType _collisionShapeType;
        bool _isTrigger{false};
        bool _isGravityEnabled{true};
        float _mass{1};


        ShapeParams _shapeParams;

        friend ::PhysicsEventManager;
        friend ::PhysicsSystem;
        friend cereal::access;

    public:
        reactphysics3d::RigidBody *rb{nullptr};
        float GetMass() const;
        bool GetIsGravityEnabled() const;
        BodyType GetBodyType() const;
        bool GetIsTrigger() const;
        CollisionShapeType GetCollisionShapeType() const;
        float GetRadius() const;
        float GetHeight() const;
        Maths::Vector3<float> GetHalfExtends() const;

        template<class Archive>
        void serialize(Archive &archive)
        {
            archive(cereal::make_nvp("mass", _mass),
                    cereal::make_nvp("gravity", _isGravityEnabled),
                    cereal::make_nvp("trigger", _isTrigger),
                    cereal::make_nvp("bodyType", _bodyType),
            cereal::make_nvp("shapeType", _collisionShapeType),
            cereal::make_nvp("shapeParams", _shapeParams.halfExtends));
        }
    };
}
#endif //QUACKENGINE_RIGIDBODY_HPP
