#include "Scene/System/RenderSystem.hpp"

#include <cstdio>

#include "Scene/Core/Ecs.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Core/Entity.hpp"

extern Ecs ecs;

void Renderer::RenderSystem::Init()
{

}


void Renderer::RenderSystem::Draw(float deltaTime)
{
    /*for (EntityId item : _entities) {
        printf("Entity", ecs.GetComponent<Transform>(item).position.x);
    }*/
}