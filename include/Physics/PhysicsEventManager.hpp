#ifndef QUACKENGINE_PHYSICSEVENTMANAGER_HPP
#define QUACKENGINE_PHYSICSEVENTMANAGER_HPP

#include "reactphysics3d/reactphysics3d.h"

class PhysicsEventManager : public rp3d::EventListener
{

private:
    void onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData) final;
    void onContact(const rp3d::CollisionCallback::CallbackData& callbackData) final;
};

#endif //QUACKENGINE_PHYSICSEVENTMANAGER_HPP
