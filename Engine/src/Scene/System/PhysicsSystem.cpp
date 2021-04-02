#include "Scene/System/PhysicsSystem.hpp"

#include "Scene/Core/World.hpp"

#include "Scene/Component/RigidBody.hpp"

#include "Scene/Component/Transform.hpp"


void PhysicsSystem::AddBoxCollider(Entity id, const Maths::Vector3f &halfExtend, const Maths::Vector3f &position,
                                   const Maths::Quaternion &rotation)
{
    rp3d::BoxShape *boxShape = World::Instance().GetPhysicsManager()->createBoxShape(
            {halfExtend.x, halfExtend.y, halfExtend.z});
    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};
    World::Instance().GetComponent<Component::RigidBody>(id).rb->addCollider(boxShape, transform);
}

void
PhysicsSystem::AddSphereCollider(Entity id, float radius, const Maths::Vector3f &position,
                                 const Maths::Quaternion &rotation)
{

    rp3d::SphereShape *sphereShape = World::Instance().GetPhysicsManager()->createSphereShape(radius);
    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};

    World::Instance().GetComponent<Component::RigidBody>(id).rb->addCollider(sphereShape, transform);
}

void
PhysicsSystem::AddCapsuleCollider(Entity id, float radius, float height, const Maths::Vector3f &position,
                                  const Maths::Quaternion &rotation)
{
    rp3d::CapsuleShape *capsuleShape = World::Instance().GetPhysicsManager()->createCapsuleShape(radius, height);
    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};
    World::Instance().GetComponent<Component::RigidBody>(id).rb->addCollider(capsuleShape, transform);
}

void PhysicsSystem::Init()
{
    for (Entity entity: _entities) {
        auto &t = World::Instance().GetComponent<Transform>(entity);
        auto &r = World::Instance().GetComponent<Component::RigidBody>(entity);

        if (!r.rb)
        r.rb = World::Instance().GetPhysicsWorld()->createRigidBody({{t.position.x, t.position.y, t.position.z},
                                                                     {t.rotation.x, t.rotation.y, t.rotation.z, t.rotation.w}});
    }
}

void PhysicsSystem::FixedUpdate(float fixedDeltaTime)
{
    //todo: faire l'update
    //todo: faire classe de traduction (transform, position, etc)
    World::Instance().GetPhysicsWorld()->update(fixedDeltaTime);
    for (Entity entity: _entities) {
        auto &t = World::Instance().GetComponent<Transform>(entity);
        auto &r = World::Instance().GetComponent<Component::RigidBody>(entity);
        const rp3d::Transform &transform = r.rb->getTransform();
        t.position = {transform.getPosition().x, transform.getPosition().y, transform.getPosition().z};
        t.rotation = {transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z,
                      transform.getOrientation().w};
        }

}
