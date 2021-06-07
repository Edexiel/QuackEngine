#include "Engine.hpp"

#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/Component/Transform.hpp"


using namespace Component;

void PhysicsSystem::Init()
{
    for (Entity entity: _entities)
    {
        SetRigidBody(entity);
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
        PhysicsSystem::SetTransform(entity, t.position, t.rotation);
    }
    for (Entity entity: _entities)
    {
        auto &t = world->GetComponent<Transform>(entity);
        auto &r = world->GetComponent<Component::RigidBody>(entity);
        const rp3d::Transform &transform = r.rb->getTransform();
        t.position = {transform.getPosition().x, transform.getPosition().y, transform.getPosition().z};
        t.rotation = {transform.getOrientation().w, transform.getOrientation().x, transform.getOrientation().y,
                      transform.getOrientation().z};
    }

    world->GetPhysicsWorld()->update(fixedDeltaTime);

    if(_isSwitchingScene)
    {
        SwitchingScene();
    }
}

void PhysicsSystem::AddBoxCollider(Entity id, const Maths::Vector3f &halfExtend, const Maths::Vector3f &position,
                                   const Maths::Quaternion &rotation)
{
    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rigidBody._collisionShapeType = CollisionShapeType::CONVEX_POLYHEDRON;
    rigidBody._shapeParams.halfExtends = halfExtend;

    rp3d::BoxShape *boxShape = Engine::Instance().GetPhysicsManager().createBoxShape(
            {halfExtend.x, halfExtend.y, halfExtend.z});


    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};

    if(Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id).rb->getNbColliders() > 0)
        rigidBody.rb->removeCollider(rigidBody.rb->getCollider(0));

    rigidBody.rb->addCollider(boxShape, transform);
    PhysicsSystem::SetBounciness(id, rigidBody._bounciness);
}

void
PhysicsSystem::AddSphereCollider(Entity id, float radius, const Maths::Vector3f &position,
                                 const Maths::Quaternion &rotation)
{
    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rigidBody._collisionShapeType = CollisionShapeType::SPHERE;
    rigidBody._shapeParams.radius = radius;

    rp3d::SphereShape *sphereShape = Engine::Instance().GetPhysicsManager().createSphereShape(radius);
    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};

    if(Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id).rb->getNbColliders() > 0)
        rigidBody.rb->removeCollider(rigidBody.rb->getCollider(0));

    rigidBody.rb->addCollider(sphereShape, transform);
    PhysicsSystem::SetBounciness(id, rigidBody._bounciness);
}

void PhysicsSystem::AddCapsuleCollider(Entity id, float radius, float height, const Maths::Vector3f &position,
                                       const Maths::Quaternion &rotation)
{

    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rigidBody._collisionShapeType = CollisionShapeType::CAPSULE;

    rigidBody._shapeParams.radius = radius;
    rigidBody._shapeParams.height = height;

    rp3d::CapsuleShape *capsuleShape = Engine::Instance().GetPhysicsManager().createCapsuleShape(radius, height);
    rp3d::Transform transform{{position.x, position.y, position.z},
                              {rotation.x, rotation.y, rotation.z, rotation.w}};

    if(Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id).rb->getNbColliders() > 0)
        rigidBody.rb->removeCollider(rigidBody.rb->getCollider(0));

    rigidBody.rb->addCollider(capsuleShape, transform);
    PhysicsSystem::SetBounciness(id, rigidBody._bounciness);
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
    if(!world->HasComponent<Component::RigidBody>(id))
        return;

    auto &rigidBody = world->GetComponent<Component::RigidBody>(id);

    if (rigidBody.rb)
        return;

    auto &t = world->GetComponent<Transform>(id);
    rigidBody.rb = world->GetPhysicsWorld()->createRigidBody({{t.position.x, t.position.y, t.position.z},
                                                       {t.rotation.x, t.rotation.y, t.rotation.z, t.rotation.w}});
    switch(rigidBody._collisionShapeType)
    {
        case CollisionShapeType::CONVEX_POLYHEDRON :
        {
            PhysicsSystem::AddBoxCollider(id, rigidBody._shapeParams.halfExtends);
            break;
        }
        case CollisionShapeType::SPHERE:
        {
            PhysicsSystem::AddSphereCollider(id, rigidBody._shapeParams.radius);
            break;
        }
        case CollisionShapeType::CAPSULE:
        {
            PhysicsSystem::AddCapsuleCollider(id, rigidBody._shapeParams.radius, rigidBody._shapeParams.height);
            break;
        }
        case CollisionShapeType::NONE:
            break;

        default:
            break;
    }
    PhysicsSystem::SetType(id, rigidBody._bodyType);
    PhysicsSystem::SetMass(id, rigidBody._mass);
    PhysicsSystem::SetIsGravityEnable(id, rigidBody._isGravityEnabled);
    if(rigidBody.rb->getNbColliders() > 0)
        PhysicsSystem::SetIsTrigger(id, rigidBody._isTrigger);

    rigidBody.rb->setUserData(reinterpret_cast<void*>(static_cast<size_t>(id)));
}

void PhysicsSystem::SetMass(Entity id, float mass)
{
    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rigidBody._mass = mass;
    rigidBody.rb->setMass(mass);

    //todo: change this code if the dev of reactphysics3d fix this bug.
    if(rigidBody._bodyType == BodyType::STATIC)
    {
        rigidBody.rb->setType(rp3d::BodyType::DYNAMIC);// Sorcellerie Obligatoire due a reactphysics3d
        rigidBody.rb->setType(rp3d::BodyType::STATIC);// Sorcellerie Obligatoire due a reactphysics3d
    }
    else if (rigidBody._bodyType == BodyType::KINEMATIC)
    {
        rigidBody.rb->setType(rp3d::BodyType::DYNAMIC);// Sorcellerie Obligatoire due a reactphysics3d
        rigidBody.rb->setType(rp3d::BodyType::KINEMATIC);// Sorcellerie Obligatoire due a reactphysics3d
    }
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

void PhysicsSystem::SetVelocity(Entity id, const Maths::Vector3f &velocity)
{
    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rigidBody.rb->setLinearVelocity({velocity.x, velocity.y, velocity.z});
}

void PhysicsSystem::SetBounciness(Entity id, float bounciness)
{
    bounciness < 0? bounciness = 0 : (bounciness > 1 ? bounciness = 1 : bounciness);

    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rigidBody._bounciness = bounciness;
    if(rigidBody.rb->getNbColliders() > 0)
        rigidBody.rb->getCollider(0)->getMaterial().setBounciness(bounciness);
}

void PhysicsSystem::SetTransform(Entity id, const Maths::Vector3f &position, const Maths::Quaternion &rotation)
{
    rp3d::Vector3 pos {position.x, position.y, position.z};
    rp3d::Quaternion rot(rotation.x, rotation.y, rotation.z, rotation.w);
    rp3d::Transform t {pos, rot};

    auto &world = Engine::Instance().GetCurrentWorld();
    auto &rigidBody = world.GetComponent<RigidBody>(id);
    auto &transform = world.GetComponent<Transform>(id);

    rigidBody.rb->setTransform(t);
    transform.position = position;
    transform.rotation = rotation;
}

void PhysicsSystem::SwitchingScene()
{
    _isSwitchingScene = false;
    auto &engine = Engine::Instance();
    Engine::Instance().SetCurrentWorld(_worldName);
    engine.GetCurrentWorld().Clear();
    Engine::Instance().LoadWorld(engine.GetCurrentWorld());
}

void PhysicsSystem::SetIsSwitchingScene(bool isSwitching)
{
    _isSwitchingScene = isSwitching;
}

void PhysicsSystem::SetWorldName(std::string name)
{
    _worldName = name;
}
