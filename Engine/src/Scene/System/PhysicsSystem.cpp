#include "Engine.hpp"

#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/Component/Transform.hpp"


using namespace Component;

void PhysicsSystem::Init()
{
    auto world = &Engine::Instance().GetCurrentWorld();
    for (Entity entity: _entities)
    {
        auto &t = world->GetComponent<Transform>(entity);
        auto &r = world->GetComponent<Component::RigidBody>(entity);

        if (!r.rb)
        {
            r.rb = world->GetPhysicsWorld()->createRigidBody({{t.position.x, t.position.y, t.position.z},
                                                               {t.rotation.x, t.rotation.y, t.rotation.z, t.rotation.w}});
        }
    }
}

void PhysicsSystem::FixedUpdate(float fixedDeltaTime)
{
    //todo: faire l'update
    //todo: faire classe de traduction (transform, position, etc)

    auto world = &Engine::Instance().GetCurrentWorld();

    for (Entity entity: _entities)
    {
        auto &t = world->GetComponent<Transform>(entity);
        auto &r = world->GetComponent<Component::RigidBody>(entity);
        rp3d::Transform newTransform({t.position.x, t.position.y, t.position.z}, {t.rotation.w, t.rotation.x, t.rotation.y, t.rotation.z});
        const rp3d::Transform &transform = r.rb->getTransform();
        if(newTransform != transform)
            r.rb->setTransform(newTransform);
    }

    world->GetPhysicsWorld()->update(fixedDeltaTime);

    for (Entity entity: _entities)
    {
        auto &t = world->GetComponent<Transform>(entity);
        auto &r = world->GetComponent<Component::RigidBody>(entity);
        const rp3d::Transform &transform = r.rb->getTransform();
        t.position = {transform.getPosition().x, transform.getPosition().y, transform.getPosition().z};
        t.rotation = {transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z,
                      transform.getOrientation().w};
    }
}

void PhysicsSystem::AddBoxCollider(Entity id, const Maths::Vector3f &halfExtend, const Maths::Vector3f &position,
                                   const Maths::Quaternion &rotation)
{
    if(Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id).rb->getNbColliders() > 0)
        return;

    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rigidBody._collisionShapeType = CollisionShapeType::CONVEX_POLYHEDRON;
    rigidBody._shapeParams.halfExtends = halfExtend;

    rp3d::BoxShape *boxShape = Engine::Instance().GetPhysicsManager().createBoxShape(
            {halfExtend.x, halfExtend.y, halfExtend.z});


    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};
    Engine::Instance().GetCurrentWorld().GetComponent<Component::RigidBody>(id).rb->addCollider(boxShape, transform);
}

void
PhysicsSystem::AddSphereCollider(Entity id, float radius, const Maths::Vector3f &position,
                                 const Maths::Quaternion &rotation)
{
    if(Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id).rb->getNbColliders() > 0)
        return;

    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rigidBody._collisionShapeType = CollisionShapeType::SPHERE;
    rigidBody._shapeParams.radius = radius;

    rp3d::SphereShape *sphereShape = Engine::Instance().GetPhysicsManager().createSphereShape(radius);
    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};


    Engine::Instance().GetCurrentWorld().GetComponent<Component::RigidBody>(id).rb->addCollider(sphereShape, transform);

    rigidBody.rb->getCollider(0)->getCollisionShape()->getType();
}

void PhysicsSystem::AddCapsuleCollider(Entity id, float radius, float height, const Maths::Vector3f &position,
                                       const Maths::Quaternion &rotation)
{
    if(Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id).rb->getNbColliders() > 0)
        return;

    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rigidBody._collisionShapeType = CollisionShapeType::CAPSULE;

    rigidBody._shapeParams.radius = radius;
    rigidBody._shapeParams.height = height;

    rp3d::CapsuleShape *capsuleShape = Engine::Instance().GetPhysicsManager().createCapsuleShape(radius, height);
    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};

    Engine::Instance().GetCurrentWorld().GetComponent<Component::RigidBody>(id).rb->addCollider(capsuleShape, transform);

    rigidBody.rb->getCollider(0)->getCollisionShape();
}

void PhysicsSystem::SetType(Entity id, const BodyType &type)
{
    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<Component::RigidBody>(id);
    rigidBody._bodyType = type;
    rigidBody.rb->setType((rp3d::BodyType) type);
}

void PhysicsSystem::SetIsTrigger(Entity id, bool isTrigger)
{
    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<Component::RigidBody>(id);
    rigidBody._isTrigger = isTrigger;
    rigidBody.rb->getCollider(0)->setIsTrigger(isTrigger);

}
void PhysicsSystem::SetRigidBody(Entity id)
{
    auto world = &Engine::Instance().GetCurrentWorld();
    auto &rigidBody = world->GetComponent<Component::RigidBody>(id);
    auto & name = world->GetComponent<Component::Name>(id);

    if (rigidBody.rb)
        return;

    auto &t = world->GetComponent<Transform>(id);
    rigidBody.rb = world->GetPhysicsWorld()->createRigidBody({{t.position.x, t.position.y, t.position.z},
                                                       {t.rotation.x, t.rotation.y, t.rotation.z, t.rotation.w}});

    rigidBody.rb->setUserData(reinterpret_cast<void*>(static_cast<size_t>(id)));
}

void PhysicsSystem::SetMass(Entity id, float mass)
{
    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rigidBody._mass = mass;
    rigidBody.rb->setMass(mass);
}

void PhysicsSystem::ResizeBoxCollider(Entity id, const Maths::Vector3f &halfExtend)
{
    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    if(rigidBody.rb->getNbColliders() > 0)
    {
        reinterpret_cast<reactphysics3d::BoxShape *>(rigidBody.rb->getCollider(0)->getCollisionShape())->setHalfExtents(
                {halfExtend.x, halfExtend.y, halfExtend.z});
        rigidBody._shapeParams.halfExtends = halfExtend;
    }
}

void PhysicsSystem::ResizeSphereCollider(Entity id, float radius)
{
    radius <= 0 ? radius = 0.001f : radius;

    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    if(rigidBody.rb->getNbColliders() > 0)
    {
        reinterpret_cast<reactphysics3d::SphereShape *>(rigidBody.rb->getCollider(0)->getCollisionShape())->setRadius(radius);

        rigidBody._shapeParams.radius = radius;
    }
}

void PhysicsSystem::ResizeCapsuleCollider(Entity id, float radius, float height)
{
    radius <= 0 ? radius = 0.001f : radius;
    radius <= 0 ? height = 0.001f : height;

    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    if(rigidBody.rb->getNbColliders() > 0)
    {
        auto *capsuleShape = reinterpret_cast<reactphysics3d::CapsuleShape *>(rigidBody.rb->getCollider(0)->getCollisionShape());
        capsuleShape->setRadius(radius);
        capsuleShape->setHeight(height);

        rigidBody._shapeParams.radius = radius;
        rigidBody._shapeParams.height = height;
    }
}

void PhysicsSystem::SetIsGravityEnable(Entity id, bool isGravityEnabled)
{
    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rigidBody.rb->enableGravity(isGravityEnabled);
    rigidBody._isGravityEnabled = isGravityEnabled;
}
