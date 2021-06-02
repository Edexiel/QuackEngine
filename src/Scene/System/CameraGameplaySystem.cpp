#include "Scene/System/CameraGameplaySystem.hpp"
#include "Engine.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Camera.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Component/CameraGameplay.hpp"
#include "Scene/Component/CharacterController.hpp"
#include "Maths/Quaternion.hpp"

using namespace Component;

CameraGameplaySystem::CameraGameplaySystem()
{
    for (Entity entity : _entities)
    {
        SearchPlayer(entity);
    }
}

void CameraGameplaySystem::Update()
{
    auto &world = Engine::Instance().GetCurrentWorld();
    for (Entity entity : _entities)
    {
        auto &cameraGameplay = world.GetComponent<CameraGameplay>(entity);
        if(world.HasComponent<Transform>(cameraGameplay.entityToFollow) && cameraGameplay.entityToFollow != entity)
        {
            auto &transformToFollow = world.GetComponent<Transform>(cameraGameplay.entityToFollow);
            auto &transform = world.GetComponent<Transform>(entity);
            transform.position = transformToFollow.position + cameraGameplay.distance;
            LookAtEntity(entity);
        }
        else
        {
            SearchPlayer(entity);
        }
    }
}

void CameraGameplaySystem::SearchPlayer(Entity id)
{
    auto &world = Engine::Instance().GetCurrentWorld();
    if(!world.HasComponent<CameraGameplay>(id))
        return;

    auto &cameraGameplay = world.GetComponent<CameraGameplay>(id);
    for(Entity entity : world.GetEntityManager()->GetEntities())
    {
        if(world.HasComponent<Component::CharacterController>(entity))
        {
            cameraGameplay.entityToFollow = entity;
            return;
        }
    }
}

void CameraGameplaySystem::LookAtEntity(Entity id)
{
    auto &world = Engine::Instance().GetCurrentWorld();
    auto &cameraGameplay = world.GetComponent<Component::CameraGameplay>(id);

    if(!world.HasComponent<Transform>(cameraGameplay.entityToFollow))
        return;

    auto &transformEntityToFollow = world.GetComponent<Transform>(cameraGameplay.entityToFollow);
    auto &transform = world.GetComponent<Transform>(id);

    transform.rotation = Maths::Quaternion::LookAt(transform.position, transformEntityToFollow.position);
}
