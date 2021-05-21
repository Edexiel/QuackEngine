#include "Scene/System/CharacterControllerSystem.hpp"
#include "reactphysics3d/reactphysics3d.h"
#include "Engine.hpp"
#include "Scene/Component/RigidBody.hpp"

using namespace Component;

bool CharacterControllerSystem::RaycastTest(Entity id)
{
    auto &transform = Engine::Instance().GetCurrentWorld().GetComponent<Transform>(id);
    auto &rigidBody = Engine::Instance().GetCurrentWorld().GetComponent<RigidBody>(id);
    rp3d::Vector3  pt1{transform.position.x,transform.position.y, transform.position.z};
    rp3d::Vector3  pt2{transform.position.x - 6,transform.position.y, transform.position.z};

    rp3d::Ray ray(pt1, pt2);
    rp3d::RaycastInfo raycastInfo;
    std::cout << "pt1: x = " << pt1.x<< ", y = " << pt1.y << ", z = " << pt1.z << "\n"
              << "pt2: x = " << pt2.x<< ", y = " << pt2.y << ", z = " << pt2.z << std::endl;
    rigidBody.rb->raycast(ray, raycastInfo);
    


}