#include "Scene/System/CharacterControllerSystem.hpp"

#include "reactphysics3d/reactphysics3d.h"
#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/RigidBody.hpp"

using namespace Component;

void CharacterControllerSystem::Update()
{
    auto &world = Engine::Instance().GetCurrentWorld();

    for(Entity entity : _entities)
    {
        auto &rigidBody = world.GetComponent<RigidBody>(entity);
        rigidBody.rb->setAngularDamping(1);
        rp3d::Material &material = rigidBody.rb->getCollider(0)->getMaterial();
        std::cout << rigidBody.rb->getCollider(0)->getMaterial().getBounciness() << std::endl;
    }
}
