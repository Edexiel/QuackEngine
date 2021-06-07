#ifndef _ENEMYMANAGERCOMPONENT_HPP
#define _ENEMYMANAGERCOMPONENT_HPP

#include "Scene/Component/ComponentBase.hpp"

struct EnemySpawnPointComponent : public Component::ComponentBase
{
    float innerRadius {0.f};
    float outerRadius {1.f};

    float spawnInterval {0.5f};
    float lastTime {0.0f};

};

#endif //_ENEMYMANAGERCOMPONENT_HPP
