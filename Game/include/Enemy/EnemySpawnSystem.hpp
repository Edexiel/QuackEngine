#ifndef QUACKENGINE_ENEMYSPAWNSYSTEM_HPP
#define QUACKENGINE_ENEMYSPAWNSYSTEM_HPP

#include "Scene/Core/System.hpp"
#include "Maths/Vector3.hpp"

namespace Component
{
    class Transform;
}

class EnemyComponent;

enum NoteType {M_UP = 0, M_DOWN, M_RIGHT, M_LEFT};

class EnemySpawnSystem : public System
{

public:

    void Update();
    void GenerateEnemies(unsigned int numberToGenerate, unsigned int nbWeakness, const Maths::Vector3f& origin, float innerRadius, float outerRadius);

};


#endif //QUACKENGINE_ENEMYSPAWNSYSTEM_HPP
