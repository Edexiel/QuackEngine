#include "Enemy/EnemySpawnSystem.hpp"

#include "Scene/Core/World.hpp"
#include "Time/TimeManager.hpp"
#include "Tools/Random.hpp"
#include "Scene/Component/Transform.hpp"

#include "Enemy/EnemySpawnPointComponent.hpp"
#include "Enemy/EnemyComponent.hpp"

void EnemySpawnSystem::Update()
{
    World& world = Engine::Instance().GetCurrentWorld();
    float time = (float)Engine::Instance().GetTimeManager().GetTime();
    for (Entity entity : _entities)
    {
        auto& spawner = world.GetComponent<EnemySpawnPointComponent>(entity);

        if (time - spawner.lastTime > spawner.spawnInterval)
        {
            auto& trs = world.GetComponent<Component::Transform>(entity);
            GenerateEnemies(1, Random::Range(1, 3), trs.position, spawner.innerRadius, spawner.outerRadius);
            spawner.lastTime = time;
            spawner.nbEnemy--;
        }

        if (spawner.nbEnemy <= 0)
        {
            world.DestroyEntity(entity);
            return;
        }
    }
}

void
EnemySpawnSystem::GenerateEnemies(unsigned int numberToGenerate, unsigned int nbWeakness, const Maths::Vector3f &origin,
                                  float innerRadius, float outerRadius)
{
    World &world = Engine::Instance().GetCurrentWorld();

    for (unsigned int i = 0; i <numberToGenerate; i++)
    {
        for (unsigned int i = 0; i < numberToGenerate; i++)
        {
            Entity id = world.CreateEntity("Enemy");

            Component::Transform trs;
            Maths::Vector3f direction{Random::Range(0.f, 1.0f), 0, Random::Range(0.0f, 1.0f)};
            direction.Normalize();
            trs.position = origin * Random::Range(innerRadius, outerRadius);
            world.AddComponent(id, trs);

            EnemyComponent enemyWeaknessDisplay;
            for (unsigned int e = 0 ; e < nbWeakness; e++)
            {
                enemyWeaknessDisplay.AddNote((NoteType)Random::Range(0,3));
            }

            world.AddComponent(id, enemyWeaknessDisplay);
        }
    }
}
