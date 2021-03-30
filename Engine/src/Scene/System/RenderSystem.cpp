#include "Scene/System/RenderSystem.hpp"

#include "Scene/Core/Types.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Component/Model.hpp"

#include "Scene/Core/World.hpp"

void RenderSystem::Init()
{

}


void RenderSystem::Draw(float deltaTime)
{
    for (Entity entity: _entities) {
        auto &t = World::Instance().GetComponent<Transform>(entity);
        auto &m = World::Instance().GetComponent<Component::Model>(entity);

        m.Draw();
    }
}