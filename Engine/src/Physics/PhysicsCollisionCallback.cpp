#include "Physics/PhysicsCollisionCallback.hpp"
#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/RigidBody.hpp"
#include "Scene/System/CharacterControllerSystem.hpp"
#include "Scene/Component//CharacterController.hpp"

void PhysicsCollisionCallback::onContact(const rp3d::CollisionCallback::CallbackData &callbackData)
{
    for (unsigned int p = 0; p < callbackData.getNbContactPairs(); p++)
    {
        // Get the contact pair
        rp3d::CollisionCallback::ContactPair contactPair = callbackData.getContactPair(p);

        rp3d::CollisionBody* body1 = contactPair.getBody1();
        auto entity1 = static_cast<Entity>(reinterpret_cast<size_t>(body1->getUserData()));
        World& world = Engine::Instance().GetCurrentWorld();

        rp3d::CollisionCallback::ContactPoint cp = contactPair.getContactPoint(0);
        rp3d::Vector3 tempNormal =  cp.getWorldNormal();
        Maths::Vector3f normal {tempNormal.x, tempNormal.y, tempNormal.z};

        if(contactPair.getEventType() == rp3d::CollisionCallback::ContactPair::EventType::ContactStart)
        {
            if(world.HasComponent<Component::CharacterController>(entity1))
                    CharacterControllerSystem::CollideWithWall(entity1, normal, cp.getPenetrationDepth());
        }
    }
}
