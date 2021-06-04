#ifndef QUACKENGINE_PHYSICSCOLLISIONCALLBACK_HPP
#define QUACKENGINE_PHYSICSCOLLISIONCALLBACK_HPP

#include "reactphysics3d/reactphysics3d.h"

class PhysicsCollisionCallback : public reactphysics3d::CollisionCallback
{
    void onContact(const rp3d::CollisionCallback::CallbackData& callbackData) final;
};

#endif //QUACKENGINE_PHYSICSCOLLISIONCALLBACK_HPP