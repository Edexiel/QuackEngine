#include "Scene/Component/RigidBody.hpp"
#include "reactphysics3d/reactphysics3d.h"
#include "Debug/Assertion.hpp"

using namespace Component;

float RigidBody::GetMass() const
{
    return _mass;
}
BodyType RigidBody::GetBodyType() const
{
    return _bodyType;
}
bool RigidBody::GetIsTrigger() const
{
    return _isTrigger;
}
CollisionShapeType RigidBody::GetCollisionShapeType() const
{
    return _collisionShapeType;
}

float RigidBody::GetRadius() const
{
    if(_collisionShapeType == CollisionShapeType::SPHERE || _collisionShapeType == CollisionShapeType::CAPSULE)
        return _shapeParams.radius;

    return 1;//todo: Assertion instead of returning 1
}

float RigidBody::GetHeight() const
{
    if(_collisionShapeType == CollisionShapeType::CAPSULE)
    return _shapeParams.height;

    return 1;//todo: Assertion instead of returning 1
}

Maths::Vector3<float> RigidBody::GetHalfExtends() const
{
    if(_collisionShapeType == CollisionShapeType::CONVEX_POLYHEDRON)
    return _shapeParams.halfExtends;

    return Maths::Vector3f::Zero();//todo: Assertion instead of returning vectorZero
}

bool RigidBody::GetIsGravityEnabled() const
{
    return _isGravityEnabled;
}

float RigidBody::GetBounciness() const
{
    return _bounciness;
}
