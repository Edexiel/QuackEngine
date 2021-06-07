#ifndef QUACKENGINE_ENEMYSPAWNSYSTEM_HPP
#define QUACKENGINE_ENEMYSPAWNSYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Maths/Vector3.hpp"

namespace Component
{
    class Transform;
}

class EnemyComponent;

class EnemySpawnSystem : public System
{

public:

    void Update();
    void GenerateEnemies(unsigned int numberToGenerate, unsigned int nbWeakness, const Maths::Vector3f& origin, float innerRadius, float outerRadius);

};


#endif //QUACKENGINE_ENEMYSPAWNSYSTEM_HPP
