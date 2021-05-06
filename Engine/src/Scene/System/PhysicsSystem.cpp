#include "Engine.hpp"

#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/Component/RigidBody.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Core/World.hpp"

#include "reactphysics3d/reactphysics3d.h"

using namespace Component;

void PhysicsSystem::Init()
{
    //todo : lol, gros bug possible si on change de world, supprime un world et qu'on reviens sur celui la
    _world = &Engine::Instance().GetCurrentWorld();

    for (Entity entity: _entities)
    {
        auto &t = _world->GetComponent<Transform>(entity);
        auto &r = _world->GetComponent<Component::RigidBody>(entity);

        if (!r.rb)
            r.rb = _world->GetPhysicsWorld()->createRigidBody({{t.position.x, t.position.y, t.position.z},
                                                               {t.rotation.x, t.rotation.y, t.rotation.z, t.rotation.w}});
    }
}

void PhysicsSystem::FixedUpdate(float fixedDeltaTime)
{
    //todo: faire l'update
    //todo: faire classe de traduction (transform, position, etc)
    for (Entity entity: _entities)
    {
        auto &t = _world->GetComponent<Transform>(entity);
        auto &r = _world->GetComponent<Component::RigidBody>(entity);
        rp3d::Transform newTransform({t.position.x, t.position.y, t.position.z}, {t.rotation.w, t.rotation.x, t.rotation.y, t.rotation.z});
        const rp3d::Transform &transform = r.rb->getTransform();
        if(newTransform != transform)
            r.rb->setTransform(newTransform);
    }

    _world->GetPhysicsWorld()->update(fixedDeltaTime);

    for (Entity entity: _entities)
    {
        auto &t = _world->GetComponent<Transform>(entity);
        auto &r = _world->GetComponent<Component::RigidBody>(entity);
        const rp3d::Transform &transform = r.rb->getTransform();
        t.position = {transform.getPosition().x, transform.getPosition().y, transform.getPosition().z};
        t.rotation = {transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z,
                      transform.getOrientation().w};
    }
}

void PhysicsSystem::AddBoxCollider(Entity id, const Maths::Vector3f &halfExtend, const Maths::Vector3f &position,
                                   const Maths::Quaternion &rotation)
{
    rp3d::BoxShape *boxShape = Engine::Instance().GetPhysicsManager().createBoxShape(
            {halfExtend.x, halfExtend.y, halfExtend.z});
    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};
    _world->GetComponent<Component::RigidBody>(id).rb->addCollider(boxShape, transform);
}

void
PhysicsSystem::AddSphereCollider(Entity id, float radius, const Maths::Vector3f &position,
                                 const Maths::Quaternion &rotation)
{

    rp3d::SphereShape *sphereShape = Engine::Instance().GetPhysicsManager().createSphereShape(radius);
    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};

    _world->GetComponent<Component::RigidBody>(id).rb->addCollider(sphereShape, transform);
}

void PhysicsSystem::AddCapsuleCollider(Entity id, float radius, float height, const Maths::Vector3f &position,
                                       const Maths::Quaternion &rotation)
{
    rp3d::CapsuleShape *capsuleShape = Engine::Instance().GetPhysicsManager().createCapsuleShape(radius, height);
    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};
    _world->GetComponent<Component::RigidBody>(id).rb->addCollider(capsuleShape, transform);
}

void PhysicsSystem::SetType(Entity id, const BodyType &type)
{
    _world->GetComponent<Component::RigidBody>(id).rb->setType((rp3d::BodyType) type);
}

void PhysicsSystem::SetIsTrigger(Entity id, bool isTrigger)
{
    _world->GetComponent<Component::RigidBody>(id).rb->getCollider(0)->setIsTrigger(isTrigger);
}
void PhysicsSystem::SetRigidBody(Entity id)
{
    auto &r = _world->GetComponent<Component::RigidBody>(id);

    if (r.rb)
        return;

    auto &t = _world->GetComponent<Transform>(id);
    r.rb = _world->GetPhysicsWorld()->createRigidBody({{t.position.x, t.position.y, t.position.z},
                                                       {t.rotation.x, t.rotation.y, t.rotation.z, t.rotation.w}});
}