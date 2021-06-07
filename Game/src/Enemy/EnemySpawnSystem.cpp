#include "Enemy/EnemySpawnSystem.hpp"

#include "Scene/Core/World.hpp"
#include "Time/TimeManager.hpp"

#include "Enemy/EnemySpawnPointComponent.hpp"

void EnemySpawnSystem::Update()
{
    World& world = Engine::Instance().GetCurrentWorld();
    float time = (float)Engine::Instance().GetTimeManager().GetTime();
    for (Entity entity : _entities)
    {
        auto& spawner = world.GetComponent<EnemySpawnPointComponent>(entity);

    }
}

void
EnemySpawnSystem::GenerateEnemies(unsigned int numberToGenerate, unsigned int nbWeakness, const Maths::Vector3f &origin,
                                  float innerRadius, float outerRadius)
{

}
