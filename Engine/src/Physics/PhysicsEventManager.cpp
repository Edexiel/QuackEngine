#include "Physics/PhysicsEventManager.hpp"

#include "Engine.hpp"
#include "Scene/Component/RigidBody.hpp"

using namespace Component;

void PhysicsEventManager::onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData)
{
//    for(unsigned int p = 0; p < callbackData.getNbOverlappingPairs(); p++)
//    {
//        rp3d::OverlapCallback::OverlapPair overlapPair = callbackData.getOverlappingPair(p);
//
//        rp3d::CollisionBody* body1 = overlapPair.getBody1();
//        rp3d::CollisionBody* body2 = overlapPair.getBody2();
//
//        auto entity1 = static_cast<Entity>(reinterpret_cast<size_t>(body1->getUserData()));
//        auto entity2 = static_cast<Entity>(reinterpret_cast<size_t>(body2->getUserData()));
//
//        World& world = Engine::Instance().GetCurrentWorld();
//        auto &rigidBody1 = world.GetComponent<Component::RigidBody>(entity1);
//        auto &rigidBody2 = world.GetComponent<Component::RigidBody>(entity2);
//
//        switch(overlapPair.getEventType())
//        {
//            case rp3d::OverlapCallback::OverlapPair::EventType::OverlapExit:
//            {
//                if(rigidBody1._overlapExit)
//                    rigidBody1._overlapExit(entity1, entity2);
//
//                if(rigidBody2._overlapExit)
//                    rigidBody2._overlapExit(entity2, entity1);
//
//                break;
//            }
//            case rp3d::OverlapCallback::OverlapPair::EventType::OverlapStart:
//            {
//                if(rigidBody1._overlapStart)
//                    rigidBody1._overlapStart(entity1, entity2);
//
//                if(rigidBody2._overlapStart)
//                    rigidBody2._overlapStart(entity2, entity1);
//
//                break;
//            }
//            case rp3d::OverlapCallback::OverlapPair::EventType::OverlapStay:
//            {
//                if(rigidBody1._overlapStay)
//                    rigidBody1._overlapStay(entity1, entity2);
//
//                if(rigidBody2._overlapStay)
//                    rigidBody2._overlapStay(entity2, entity1);
//
//                break;
//            }
//            default:
//            {
//                break;
//            }
//        }
//    }
}
void PhysicsEventManager::onContact(const rp3d::CollisionCallback::CallbackData& callbackData)
{
//    for (unsigned int p = 0; p < callbackData.getNbContactPairs(); p++)
//    {
//        // Get the contact pair
//        rp3d::CollisionCallback::ContactPair contactPair = callbackData.getContactPair(p);
//
//        rp3d::CollisionBody* body1 = contactPair.getBody1();
//        rp3d::CollisionBody* body2 = contactPair.getBody2();
//        auto entity1 = static_cast<Entity>(reinterpret_cast<size_t>(body1->getUserData()));
//        auto entity2 = static_cast<Entity>(reinterpret_cast<size_t>(body2->getUserData()));
//        World& world = Engine::Instance().GetCurrentWorld();
//
//        auto &rigidBody1 = world.GetComponent<Component::RigidBody>(entity1);
//        auto &rigidBody2 = world.GetComponent<Component::RigidBody>(entity2);
//
//        switch(contactPair.getEventType())
//        {
//            case rp3d::CollisionCallback::ContactPair::EventType::ContactExit:
//            {
//                if(rigidBody1._contactExit)
//                    rigidBody1._contactExit(entity1, entity2);
//
//                if(rigidBody2._contactExit)
//                    rigidBody2._contactExit(entity2, entity1);
//
//                break;
//            }
//            case rp3d::CollisionCallback::ContactPair::EventType::ContactStart:
//            {
//                if(rigidBody1._contactStart)
//                    rigidBody1._contactStart(entity1, entity2);
//
//                if(rigidBody2._contactStart)
//                    rigidBody2._contactStart(entity2, entity1);
//
//                break;
//            }
//            case rp3d::CollisionCallback::ContactPair::EventType::ContactStay:
//            {
//                if(rigidBody1._contactStay)
//                    rigidBody1._contactStay(entity1, entity2);
//
//                if(rigidBody2._contactStay)
//                    rigidBody2._contactStay(entity2, entity1);
//
//                break;
//            }
//            default:
//            {
//                break;
//            }
//        }
//    }
}